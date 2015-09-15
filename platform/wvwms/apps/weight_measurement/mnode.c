/*
 * Copyright (c) 2011, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

#include "contiki.h"
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "net/uip.h"
#include "net/uip-ds6.h"
#include "net/uip-debug.h"

#include "sys/node-id.h"

#include "simple-udp.h"
#include "servreg-hack.h"
#include "wvwms_functions.h"
#include "dev/serial-line.h"
#include "dev/uart0.h"

#include <stdio.h>
#include <string.h>

#define UDP_PORT 3000
#define SERVICE_ID 190
#define RX_BUFFER_SIZE 255

#define SEND_INTERVAL		(1 * CLOCK_SECOND)
#define SEND_TIME		(random_rand() % (SEND_INTERVAL))

static struct simple_udp_connection unicast_connection;
extern process_event_t arm_message;

void send_message(unsigned char *buf, uint8_t size);
/*---------------------------------------------------------------------------*/
PROCESS(unicast_sender_process, "Unicast sender example process");

AUTOSTART_PROCESSES(&unicast_sender_process);

/*---------------------------------------------------------------------------*/
static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  uint8_t size, i;
  unsigned char buffer[RX_BUFFER_SIZE];
  unsigned char ok[]={0x1, 0xFE};
  printf("\n\rDR %d FP %d WL %d\n\r",
	  receiver_port, sender_port, datalen);
  if((*data)==FRAME_START_1 && (*(data+1))==FRAME_START_2 &&  (*(data+2))>0){
	  size = *(data+2);
	  printf("\n\rUDP Received size:%d :\n\r", 0xFF & size);
	  if((*(data+3))==0){
		  if((*(data+4))==0) {
			  printf("VDD disabled \n\r");
			  arm_power_off();
		  }
		  else{
			  printf("VDD enabled \n\r");
			  arm_power_on();
		  }
		  send_message(ok, sizeof(ok));
	  }
	  else{
		  for(i=0; i<size;i++){
		    printf("0x%02x |", (0xFF & *((char *)data+3+i)));
		  	buffer[i] = *((char *)data+3+i);
		  }
		  printf("\n\r");
		  send_arm(buffer, size);
	  }
  }
}

static void
set_global_address(void)
{
  uip_ipaddr_t ipaddr;
  int i;
  uint8_t state;

  uip_ip6addr(&ipaddr, 0xbbbb, 0, 0, 0, 0, 0, 0, 100);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

  printf("IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
      printf("\n");
    }
  }
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(unicast_sender_process, ev, data)
{
  uip_ipaddr_t addr;
  uint8_t i;
  unsigned char *ptr;

  PROCESS_BEGIN();

  servreg_hack_init();

  set_global_address();

  simple_udp_register(&unicast_connection, UDP_PORT,
                      NULL, UDP_PORT, receiver);

  wvwms_init();
  uip_create_linklocal_allnodes_mcast(&addr);
  while(1) {
//    printf("Waiting for event \n\r");
    PROCESS_WAIT_EVENT();
    if(ev != 122) printf("\n\rEv:%d\n\r",ev);
    if(ev == arm_message) {
//      ptr = (unsigned char *) data;
//      printf("\nFROM ARM %u: ", (unsigned int) 0xFF & *ptr);
//      for(i=0; i<=*(char *)ptr;i++)
//    	  printf("0x%02x |",  (unsigned int)0xFF & (*(ptr+i)));
//      printf("\n\r");
//      send_message((unsigned char *) data, (uint8_t)(*((unsigned char *)data))+1);
    	simple_udp_sendto(&unicast_connection, (unsigned char *) data,
    			(uint8_t)(*((unsigned char *)data))+1, &addr);
    }else{
    	printf("\n\rEv:%d\n\r",ev);
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

void send_message(unsigned char *buf, uint8_t size)
{
	uip_ipaddr_t addr;
//	printf("\n\rUDP send\n\r");
	uip_create_linklocal_allnodes_mcast(&addr);
	simple_udp_sendto(&unicast_connection, buf, size, &addr);
}

