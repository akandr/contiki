#include "gpio_actuator.h"

void gpio_actuator_init(void)
{
    MCP_ENABLE_DIR;
    MCP_ENABLE_LOW;
    ARM_CS_DIR;
    ARM_CS_HI;
}

