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
//	printf("*");
	_DINT();
	if((cnt==0)&&(c==FRAME_START_1)){
		cnt++;
		goto exit;
	}
	else if((cnt==1)&&(c==FRAME_START_2)){
		cnt++;
		goto exit;
	}
	else if((cnt == 0)||(cnt== 1)) {
		cnt=0;
		frame_size=0;
		goto exit;
	}
	else if(cnt==2){
		frame_size=c;
		rxbuf[cnt]=frame_size;
		cnt++;
		goto exit;
	}
	else if(cnt>2 && (cnt<(frame_size+3))){
		rxbuf[cnt]=c;
		cnt++;
		goto exit;
	}
	else{
		memcpy(msg, rxbuf+2, frame_size+1);
//		for(i=0;i<=frame_size;i++){
//			msg[i]=rxbuf[2+i];
//			//printf(" %02x|", (unsigned int) 0xFF & msg[i]);
//		}
		printf("!\n");
		cnt=0;
		frame_size=0;
		_EINT();
		process_post(PROCESS_BROADCAST, arm_message, msg);
	}
exit:
	_EINT();
	return 0;
}

void wvwms_init(void)
{
    MCP_ENABLE_DIR;
    MCP_ENABLE_HI; //power up the arm
    P1SEL = P1SEL | mcuint2mask;
    P1DIR |= mcuint2mask;
    MEM_CS_DIR;
    MEM_DESELECT;
    ARM_CS_DIR;
    ARM_CS_HI;
    cnt=0;
    frame_size=0;
    uart0_init(500000);
    uart0_set_input(&arm_handler);
    arm_message = process_alloc_event();
    leds_off(LEDS_RED | LEDS_GREEN| LEDS_BLUE| LEDS_YELLOW);
    printf("%s executed\n\r", __func__);
}

void arm_power_off(void)
{
	MCP_ENABLE_LOW;
}

void arm_power_on(void)
{
	MCP_ENABLE_HI;
}

void send_arm(unsigned char *data, uint8_t size)
{
	uint8_t i;
	uart0_writeb(FRAME_START_1);
	uart0_writeb(FRAME_START_2);
	uart0_writeb((unsigned char)size);
	printf("Writing uart0: \n\r");
	for(i=0;i<size;i++){
		printf("0x%02x |", *(data+i));
		uart0_writeb(*(data+i));
	}
	printf("\n\r");
}

void wvwms_test(void)
{
	unsigned char data[] = "this is msp\n";
	leds_toggle(LEDS_RED | LEDS_GREEN| LEDS_BLUE| LEDS_YELLOW);
	printf(".");
	send_arm(data, sizeof(data));
}


