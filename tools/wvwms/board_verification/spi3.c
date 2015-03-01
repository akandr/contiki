#include <msp430f5418a.h>
#include "msp_def_v2.h"

void uart_send_byte(char byte);
void dbg(char *s);
void io_config(void);
void uart_init(void);
void cc_send_byte(char byte);
void cc_spi_init(void);
void cc_test(void);
void cc_init(void);
void dbg_reg(char reg);
void arm_send_byte(char byte);
void mem_send_byte(char byte);
void mem_spi_init(void);
void mem_test(void);
void arm_test(void);
void arm_uart_init(void);
volatile static char spi_flag;
void arm_dbg(char *s);



int main(void)
{
    /* Hold the watchdog timer so it doesn't reset our chip */
   WDTCTL = WDTPW + WDTHOLD;
   io_config();
   uart_init();
   cc_spi_init();
   cc_init();
   mem_spi_init();
   arm_uart_init();
   P6OUT = led1mask | led2mask| led0mask; // clear all leds
   volatile int i;
   __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled
   dbg("\n\n\n\n\n\n\n\nWVWMS unit test program \n\n");
    char cntr = 0;
    MCP_ENABLE_HI;
    for( ; ; ) {
        LEDPORT = LEDPORT ^ (led0mask);
        LEDPORT = LEDPORT ^ (led1mask);
        LEDPORT = LEDPORT ^ (led2mask);
        LEDPORT = LEDPORT ^ (led3mask);
        LEDPORT = LEDPORT ^ (led4mask);
        LEDPORT = LEDPORT ^ (led5mask);
        LEDPORT = LEDPORT ^ (led6mask);
        LED7PORT = LED7PORT ^ (led7mask);
        for( i = 0; i < 20000; i++ );
	dbg("loop\n");
        cc_test();
	mem_test();
	arm_test();
    }
}


void arm_uart_init(void)
{
    P3SEL |= ARM_RX_PIN;
    P3SEL |= ARM_TX_PIN;
    UCA0CTL0 = 0;			      // all settings to 0
    UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0CTL1 |= UCRXEIE;
    UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA0BR1 = 0;                              // 1MHz 115200
    UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine
    UCA0IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt
}



void mem_test(void)
{
	MEM_SELECT;
	mem_send_byte(0x9F);
	mem_send_byte(0x9F);
	mem_send_byte(0x9F);
	mem_send_byte(0x9F);
	mem_send_byte(0x9F);
	mem_send_byte(0x9F);
	MEM_DESELECT;
}

void arm_test(void)
{
	__delay_cycles(100000);
	__delay_cycles(100000);
	arm_send_byte(0x77);
	arm_send_byte(0x77);
}



void cc_init(void)
{
  CC_RESET_HI;
  CC_VREG_EN_LOW;
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  CC_VREG_EN_HI;
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  CC_RESET_LOW;
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  CC_RESET_HI;
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
  __delay_cycles(100000);
}

void cc_test(void)
{
  cc_send_byte(0x00);
}

void io_config(void)
{
    LEDDIR = LEDDIR | (led0mask | led1mask | led2mask | led3mask | led4mask |
		    led5mask | led6mask);
    LED7DIR = LED7DIR | led7mask;

    P3DIR = P3DIR & (~(input0mask | input1mask));
    MCP_ENABLE_DIR;
    MCP_ENABLE_LOW;
    P1SEL = P1SEL | mcuint2mask;
    P1DIR |= mcuint2mask;
    P4DIR |= CC_RESET | CC_VREG_EN;
    P4OUT |= CC_RESET | CC_VREG_EN;
    MEM_CS_DIR;
    MEM_DESELECT;
    ARM_CS_DIR;
    ARM_CS_HI;
    MEM_HOLD_DIR;
    MEM_HOLD_HI;
}

void uart_init(void)
{
    P5SEL |= URXpin;
    P5SEL |= UTXpin;
    UCA1CTL0 = 0;			      // all settings to 0
    UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA1CTL1 |= UCSSEL_2;                     // SMCLK
    UCA1CTL1 |= UCRXEIE;
    UCA1BR0 = 9;                              // 1MHz 115200 (see User's Guide)
    UCA1BR1 = 0;                              // 1MHz 115200
    UCA1MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine
    UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt
}

void dbg(char *s)
{
	char c;
	// Loops through each character in string 's'
	while (c = *s++) {
		uart_send_byte(c);
	}
}

void arm_dbg(char *s)
{
	char c;
	// Loops through each character in string 's'
	while (c = *s++) {
		arm_send_byte(c);
	}
}

void dbg_reg(char reg)
{
  int i;
  dbg(" 0b");
  for(i=7;i>=0;i--){
	if((reg&(1<<i)) == 0)
		uart_send_byte('0');
	else
		uart_send_byte('1');
  }
  dbg("\n");
}

void uart_send_byte(char byte)
{
    while (!(UCA1IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA1TXBUF = byte;                       // TX byte
}

void arm_send_byte(char byte)
{
    while (!(UCA0IFG&UCTXIFG));
    UCA0TXBUF = byte;
}

void mem_spi_init(void)
{
  spi_flag = 'E';
  SET_MEM_SPI;
  UCB1CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCB1CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
  UCB1CTL1 |= UCSSEL_2;                     // SMCLK
  UCB1BR0 = 0x02;                           // /2
  UCB1BR1 = 0;                              //
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCB1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void cc_spi_init(void)
{
  SET_CC_SPI;
  UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCB0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;                           // /2
  UCB0BR1 = 0;                              //
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCB0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void cc_send_byte(char byte)
{
  while (!(UCB0IFG&UCTXIFG));
  CC_SELECT;
  __delay_cycles(10);
  UCB0TXBUF = byte;
  __delay_cycles(10);
  while (!(UCB0IFG&UCTXIFG));
  CC_DESELECT;
}

void mem_send_byte(char byte)
{
  spi_flag = 'M';
  while (!(UCB1IFG&UCTXIFG));
  __delay_cycles(10);
  UCB1TXBUF = byte;
  __delay_cycles(10);
}

void __attribute__ ((interrupt(USCI_B1_VECTOR))) USCI_B1_ISR (void)
{
  switch(UCB1IV){
	case 0:break;                             // Vector 0 - no interrupt
	case 2:				       // Vector 2 - RXIFG
		dbg("MEM SPI data ");
		dbg_reg(UCB1RXBUF);
		break;
	case 4:break;                             // Vector 4 - TXIFG
	default: break;
  }
}


void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
{
  switch(UCA0IV){
	case 0:break;                             // Vector 0 - no interrupt
	case 2:                                   // Vector 2 - RXIFG
		arm_dbg("\nARM data\n");
		arm_send_byte(UCA0RXBUF);
		break;
	case 4:break;                             // Vector 4 - TXIFG
	default: break;
  }
}



void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
{
  switch(UCA1IV){
	case 0:break;                             // Vector 0 - no interrupt
	case 2:                                   // Vector 2 - RXIFG
		dbg("\nUART input\n");
		dbg_reg(UCA1RXBUF);
		break;
		break;
	case 4:break;                             // Vector 4 - TXIFG
	default: break;
  }
}

void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)
{
  switch(UCB0IV){
	case 0: break;                          // Vector 0 - no interrupt
	case 2:                                 // Vector 2 - RXIFG
		dbg("CC: SPI data ");
		dbg_reg(UCB0RXBUF);
		break;
	case 4: break;                          // Vector 4 - TXIFG
	default: break;
  }
}

