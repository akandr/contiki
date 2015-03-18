#include "wvwms_functions.h"
#include "dev/leds.h"
#include "dev/uart0.h"
#include "contiki.h"

unsigned char cnt;
unsigned char frame_size;
unsigned char rxbuf[RXBUF_SIZE];
unsigned char msg[RXBUF_SIZE];
process_event_t arm_message;

PROCESS(test_serial_process, "Serial test process");
AUTOSTART_PROCESSES(&test_serial_process);

int arm_handler(unsigned char c)
{
	int i;
	if((!cnt)&&(c==FRAME_START_1)) cnt++;
	if((cnt==1)&&(c==FRAME_START_2)){
		cnt++;
	} else {
		cnt=0;
	}
	if(cnt==2) frame_size=c;
	if(cnt>2){
		rxbuf[cnt]=c;
		cnt++;
	}
	if(cnt>=(frame_size+2)){
		for(i=0;i<=frame_size;i++){
			msg[i]=rxbuf[2+i];
		}
		cnt=0;
		frame_size=0;
		process_post(PROCESS_BROADCAST, arm_message, msg);
	}
	return 0;
}

void wvwms_init(void)
{
    MCP_ENABLE_DIR;
    MCP_ENABLE_HI;
    P1SEL = P1SEL | mcuint2mask;
    P1DIR |= mcuint2mask;
    MEM_CS_DIR;
    MEM_DESELECT;
    ARM_CS_DIR;
    ARM_CS_HI;
    cnt=0;
    frame_size=0;
    uart0_init(115200);
    uart0_set_input(&arm_handler);
    printf("%s executed\n", __func__);
}

void wvwms_test(void)
{
	leds_off(LEDS_RED | LEDS_GREEN| LEDS_BLUE| LEDS_YELLOW);
	printf("This is wvwms test %s %s\n", __DATE__, __TIME__);
	uart0_writeb('x');
}

PROCESS_THREAD(test_serial_process, ev, data)
{
  int i;
  static struct etimer et;

  PROCESS_BEGIN();

  etimer_set(&et, CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_EVENT();

    if (etimer_expired(&et)) {
      printf("Waiting for serial data\n");
      etimer_restart(&et);
    }

    if(ev == arm_message) {
      for(i=0; i<*(char *)data;i++)
    	  printf("%c", *((char* )data+1+i));
    }
  }

  PROCESS_END();
}
