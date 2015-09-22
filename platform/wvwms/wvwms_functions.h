//#include "contiki.h"
#include <stdio.h>

// ---------------- WVWMS platform hardware definitions ----------------
#define led0mask  (0x01 << 3)
#define led1mask  (0x01 << 2)
#define led2mask  (0x01 << 1)
#define led3mask  (0x01 << 4)
#define led4mask  (0x01 << 5)
#define led5mask  (0x01 << 6)
#define led6mask  (0x01 << 7)
#define led7mask  (0x01 << 4)

#define LEDPORT   P6OUT
#define LED7PORT  P7OUT
#define LEDDIR    P6DIR
#define LED7DIR   P7DIR

#define input0mask (0x01 << 6)
#define input1mask (0x01 << 7)
#define mcuint2mask (0x01 << 2)

#define MCP_ENABLE_BIT  BIT0
#define MCP_ENABLE_HI	P6OUT|=MCP_ENABLE_BIT
#define MCP_ENABLE_LOW	P6OUT&=~MCP_ENABLE_BIT
#define MCP_ENABLE_DIR	P6DIR |= MCP_ENABLE_BIT; P6SEL &=~MCP_ENABLE_BIT

#define MEM_CS_DIR P4DIR |= BIT7; P4SEL &=~BIT7
#define MEM_SELECT P4OUT &= ~BIT7
#define MEM_DESELECT P4OUT |= BIT7

#define ARM_CS_DIR P3DIR |= BIT6; P3SEL &=~BIT6
#define ARM_CS_LOW P3OUT&=~BIT6
#define ARM_CS_HI  P3OUT|=BIT6
//------------------------------------------------------------------

#define RXBUF_SIZE 32
#define FRAME_START_1 0x7A
#define FRAME_START_2 0xA7

//void wvwms_init(void);
//void wvwms_test(void);
//void arm_power_off(void);
//void arm_power_on(void);
//void send_arm(unsigned char *data, uint8_t size);
