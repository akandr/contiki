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
 *         Leds arch specific file for the WiSMote platform
 * \author
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */

#include "contiki-conf.h"
#include "dev/leds.h"

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
    LEDPORT &= ~BIT1;
  } else {
    LEDPORT |= BIT1;
  }
  if(leds & LEDS_YELLOW) {
    LEDPORT &= ~BIT2;
  } else {
    LEDPORT |= BIT2;
  }
  if(leds & LEDS_RED) {
    LEDPORT &= ~BIT3;
  } else {
    LEDPORT |= BIT3;
  }
  if(leds & LEDS_BLUE) {
    LEDPORT &= ~BIT4;
  } else {
    LEDPORT |= BIT4;
  }

}
/*---------------------------------------------------------------------------*/
