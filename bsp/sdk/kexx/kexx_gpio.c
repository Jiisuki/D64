/** @file
 *  @brief Implementation of GPIO Drivers.
 */

/** @addtogroup GPIO
 *  @{ */

#include "kexx_gpio.h"

/* Initialises the GPIO pin. */
void GPIO_init(GPIO_Type* base, const uint32_t pin, const GPIOPinConfig_t* const config)
{
    assert(config);
    if( config->pinDirection == GPIOPinDirection_Input)
    {
        base->PDDR &= ~(1u << pin); /* set direction */
        base->PIDR &= ~(1U << pin); /* clear input disable */
    }
    else
    {
        GPIO_writePinOutput(base, pin, config->outputLogic);
        base->PDDR |= (1u << pin);
    }
}

/** @} *//* end group */

