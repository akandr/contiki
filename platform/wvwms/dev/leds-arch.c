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

/**
 * \file
 *         Leds arch specific file for the WVWMS platform
 * \author
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 *         Artur Andrzejczak <andrzejczak@dmcs.pl>
 */

#include "contiki-conf.h"
#include "dev/leds.h"

#define led0mask  (0x01 << 3)
#define led1mask  (0x01 << 2)
#define led2mask  (0x01 << 1)
#define led3mask  (0x01 << 4)
#define led4mask  (0x01 << 5)
#define led5mask  (0x01 << 6)
#define led6mask  (0x01 << 7)
#define led7mask  (0x01 << 4)
/*
#define LEDS_YELLOW led0mask
#define LEDS_GREEN  led1mask
#define LEDS_RED    led2mask
#define LEDS_BLUE   led3mask
*/

#define LEDPORT   P6OUT
#define LED7PORT  P7OUT
#define LEDDIR    P6DIR
#define LED7DIR   P7DIR

/*---------------------------------------------------------------------------*/
void leds_arch_init(void)
{
  LEDDIR = LEDDIR | (led0mask | led1mask | led2mask | led3mask | led4mask |
					    led5mask | led6mask);
  LED7DIR = LED7DIR | led7mask;
}
/*---------------------------------------------------------------------------*/
unsigned char leds_arch_get(void)
{
  return ((LEDPORT)&(0xFE))|((0x01 & (LED7PORT>>4)));
}
/*---------------------------------------------------------------------------*/
void leds_arch_set(unsigned char leds)
{	
  if(leds & LEDS_GREEN) {
    LEDPORT &= ~led0mask;
  } else {
    LEDPORT |= led0mask;
  }
  if(leds & LEDS_YELLOW) {
    LEDPORT &= ~led1mask;
  } else {
    LEDPORT |= led1mask;
  }
  if(leds & LEDS_RED) {
    LEDPORT &= ~led2mask;
  } else {
    LEDPORT |= led2mask;
  }
  if(leds & LEDS_BLUE) {
    LEDPORT &= ~led3mask;
  } else {
    LEDPORT |= led3mask;
  }

}
/*---------------------------------------------------------------------------*/
