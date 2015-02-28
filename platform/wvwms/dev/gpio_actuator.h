#include "conitki.h"

// ---------------- WVWMS platform hardware definitions ----------------
#define MCP_ENABLE_BIT  BIT0
#define MCP_ENABLE_HI	P6OUT|=MCP_ENABLE_BIT
#define MCP_ENABLE_LOW	P6OUT&=~MCP_ENABLE_BIT
#define MCP_ENABLE_DIR	P6DIR |= MCP_ENABLE_BIT; P6SEL &=~MCP_ENABLE_BIT

#define ARM_CS_DIR P3DIR |= BIT6; P3SEL &=~BIT6
#define ARM_CS_LOW P3OUT&=~BIT6
#define ARM_CS_HI  P3OUT|=BIT6

//------------------------------------------------------------------




