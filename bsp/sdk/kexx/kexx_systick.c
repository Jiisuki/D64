/** @file
 *  @brief Implements the Systick handler and option to register a callback.
 */

#include "kexx_systick.h"
#include "mcu.h"
#include <stdint.h>

/** @brief Systick storage class. */
typedef struct
{
    Systick_CallbackFcn_t callback; //!< Callback that runs for each systick.
} Systick_t;

/* Local instance of the systick class. */
static Systick_t self;

/*============================================================================*/
/* Initialises the Systick using a provided tick time in microseconds.        */
/*============================================================================*/
void Systick_init(uint32_t time_us)
{
    self.callback = (void*) 0;

    const uint32_t ticks = SystemCoreClock / 1000000 * time_us;
    SysTick_Config(ticks);
}

/*============================================================================*/
/* Registers a callback to run for each interrupt.                            */
/*============================================================================*/
void Systick_registerCallback(const Systick_CallbackFcn_t const callback)
{
    self.callback = callback;
}

/*============================================================================*/
/* Implements the interrupt vector for Systick.                               */
/*============================================================================*/
void SysTick_Handler(void)
{
    if (self.callback)
    {
        self.callback();
    }
}
