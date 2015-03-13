#include "wvwms_functions.h"
#include "dev/leds.h"
#include "dev/uart0.h"
#include "contiki.h"
#include "dev/serial-line.h"

int cnt;

int arm_handler(unsigned char c)
{
	printf("ARM handler! %c\n", c);
	cnt++;
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
    uart0_init(115200);
    uart0_set_input(&arm_handler);
    printf("%s executed\n", __func__);
}

void wvwms_test(void)
{
	leds_off(LEDS_RED | LEDS_GREEN| LEDS_BLUE| LEDS_YELLOW);
	printf("This is wvwms test %s %s %i\n", __DATE__, __TIME__,cnt);
	uart0_writeb('x');
	leds_toggle(LEDS_GREEN);
	clock_wait(2);
	leds_toggle(LEDS_YELLOW);
	clock_wait(2);
	leds_toggle(LEDS_RED);
	clock_wait(2);
	leds_toggle(LEDS_BLUE);
	clock_wait(10);
}

