#include "contiki.h"

#define led0mask  (0x01 << 3)
#define led1mask  (0x01 << 2)
#define led2mask  (0x01 << 1)
#define led3mask  (0x01 << 4)
#define led4mask  (0x01 << 5)
#define led5mask  (0x01 << 6)
#define led6mask  (0x01 << 7)
#define led7mask  (0x01 << 4)

#define LEDS_YELLOW led0mask
#define LEDS_GREEN  led1mask
#define LEDS_RED    led2mask
#define LEDS_BLUE   led3mask

#define LEDPORT   P6OUT
#define LED7PORT  P7OUT
#define LEDDIR    P6DIR
#define LED7DIR   P7DIR

void leds_arch_init(void);
unsigned char leds_arch_get(void);
void leds_arch_set(unsigned char leds);
