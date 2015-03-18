#include "wvwms_functions.h"
#include "dev/leds.h"
#include "dev/uart0.h"
#include "contiki.h"

uint8_t cnt;
uint8_t frame_size;
unsigned char rxbuf[RXBUF_SIZE];
unsigned char msg[RXBUF_SIZE];

process_event_t arm_message;

int arm_handler(unsigned char c)
{
	uint16_t i;
	if((cnt==0)&&(c==FRAME_START_1)){
		cnt++;
		return 0;
	}
	else if((cnt==1)&&(c==FRAME_START_2)){
		cnt++;
		return 0;
	}
	else if((cnt == 0)||(cnt== 1)) {
		cnt=0;
		frame_size=0;
		return 0;
	}
	else if(cnt==2){
		frame_size=c;
		rxbuf[cnt]=frame_size;
		cnt++;
		return 0;
	}
	else if(cnt>2 && (cnt<(frame_size+3))){
		rxbuf[cnt]=c;
		cnt++;
		return 0;
	}
	else{
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
    arm_message = process_alloc_event();
    printf("%s executed\n", __func__);
}

void arm_power_off(void)
{
	MCP_ENABLE_LOW;
}

void arm_power_on(void)
{
	MCP_ENABLE_HI;
}

void send_arm(char *data, uint8_t size)
{
	uint8_t i;
	uart0_writeb(FRAME_START_1);
	uart0_writeb(FRAME_START_2);
	uart0_writeb((unsigned char)size);
	for(i=0;i<size;i++){
		uart0_writeb(*(data+i));
	}
}

void wvwms_test(void)
{
	unsigned char data[] = "this is msp\n";
	leds_toggle(LEDS_RED | LEDS_GREEN| LEDS_BLUE| LEDS_YELLOW);
	printf("This is wvwms test %s %s\n", __DATE__, __TIME__);
	send_arm(data, sizeof(data));
}


