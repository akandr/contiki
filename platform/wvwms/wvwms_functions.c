#include "wvwms_functions.h"

void wvwms_init(void)
{
    MCP_ENABLE_DIR;
    MCP_ENABLE_LOW;
    P1SEL = P1SEL | mcuint2mask;
    P1DIR |= mcuint2mask;
    MEM_CS_DIR;
    MEM_DESELECT;
    ARM_CS_DIR;
    ARM_CS_HI;
}

void wvwms_test(void)
{
	printf("This is wvwms test %s %s", __DATE__, __TIME__);
}
