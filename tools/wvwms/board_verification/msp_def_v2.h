#include <msp430f5418a.h>
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

#define URXpin	BIT6
#define UTXpin	BIT7

#define CCmosi BIT1
#define CCmiso BIT2
#define CCcs   BIT0
#define CCsclk BIT3

#define SET_CC_SPI	P3DIR |= CCcs;\
			P3SEL |= CCmosi;\
			P3SEL |= CCmiso;\
			P3SEL |= CCsclk;\
			P3SEL &= ~CCcs;\
			P3OUT |= CCcs

#define SET_MEM_SPI	P3SEL |= BIT7;\
			P5SEL |= BIT4;\
			P5SEL |= BIT5;

#define CC_CS_LOW P3OUT&=~CCcs
#define CC_CS_HI P3OUT|=CCcs
#define CC_SELECT	CC_CS_LOW
#define CC_DESELECT	CC_CS_HI

#define CC_RESET BIT1
#define CC_VREG_EN BIT0

#define CC_RESET_HI   P4OUT|=CC_RESET
#define CC_RESET_LOW  P4OUT&=~CC_RESET
#define CC_VREG_EN_HI  P4OUT|=CC_VREG_EN
#define CC_VREG_EN_LOW P4OUT&=~CC_VREG_EN

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

#define ARM_RX_PIN BIT5
#define ARM_TX_PIN BIT4

#define MEM_HOLD_DIR P4DIR |= BIT6
#define MEM_HOLD_LOW P4OUT&=~BIT6
#define MEM_HOLD_HI  P4OUT|=BIT6
