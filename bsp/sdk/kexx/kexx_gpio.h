/** @file
 *  @defgroup GPIO GPIO Drivers
 *  @ingroup KEXX
 *  @brief GPIO driver (CS + name port)
 */

#pragma once

/** @addtogroup GPIO
 *  @{ */

#include "mcu.h"
#include <assert.h>

/** @name PTx GPIO Banks.
 *  Ports definitions. Links to the correct GPIO bank.
 *  Short defines for pin function base addresses, table 34.7-9 in manual.
 *  Each GPIO name corresponds to a GPIO bank, which is linked ahead below.
 *  @{ */
#define PTA GPIOA
#define PTB GPIOA
#define PTC GPIOA
#define PTD GPIOA
#define PTE GPIOB
#define PTF GPIOB
#define PTG GPIOB
#define PTH GPIOB
#define PTI GPIOC
/** @} */

/** @name PTx_OFFSET GPIO port bank base offset.
 *  Base offsets for each gpio group, it's the same for the port settings
 *  as the gpio base settings.
 *  @{ */
#define PTA_OFFSET PORT_PUE0_PTAPE0_SHIFT
#define PTB_OFFSET PORT_PUE0_PTBPE0_SHIFT
#define PTC_OFFSET PORT_PUE0_PTCPE0_SHIFT
#define PTD_OFFSET PORT_PUE0_PTDPE0_SHIFT
#define PTE_OFFSET PORT_PUE1_PTEPE0_SHIFT
#define PTF_OFFSET PORT_PUE1_PTFPE0_SHIFT
#define PTG_OFFSET PORT_PUE1_PTGPE0_SHIFT
#define PTH_OFFSET PORT_PUE1_PTHPE0_SHIFT
#define PTI_OFFSET PORT_PUE2_PTIPE0_SHIFT
/** @} */

/** @brief GPIO direction. */
typedef enum
{
    GPIOPinDirection_Input = 0U,  /**< GPIO defined as an input. */
    GPIOPinDirection_Output = 1U, /**< GPIO defined as an output. Also disables internal pullup. */
} GPIOPinDirection_t;

/*!
 * @brief The GPIO pin configuration structure.
 *
 * Each pin can only be configured as either an output pin or an input pin at a time.
 * If configured as an input pin, leave the outputConfig unused.
 * Note that in some use cases, the corresponding port property should be configured in advance
 *        with the PORT_SetPinConfig().
 */
typedef struct
{
    GPIOPinDirection_t pinDirection; /*!< GPIO direction, input or output */
    /* Output configurations; ignore if configured as an input pin */
    uint8_t outputLogic; /*!< Set a default output logic, which has no use in input */
} GPIOPinConfig_t;

/***************************************************************************//**
 * @brief Initialises the GPIO pin.
 *
 * @param base Base address to GPIO addresses.
 * @param pin Pin number (must include the offset to the base address).
 * @param config Pin configuration structure.
 ******************************************************************************/
void GPIO_init(GPIO_Type* base, const uint32_t pin, const GPIOPinConfig_t* const config);

/***************************************************************************//**
 * @brief Writes the output of the GPIO pin.
 *
 * @param base Base address to GPIO addresses.
 * @param pin Pin number (must include the offset to the base address).
 * @param value 1 for high output, 0 for ground.
 ******************************************************************************/
static inline void GPIO_writePinOutput(GPIO_Type* base, uint32_t pin, uint8_t value)
{
    if(value == 0U){
        base->PCOR = 1U << pin;
    } else {
        base->PSOR = 1U << pin;
    }
}

/***************************************************************************//**
 * @brief Sets the output of all GPIO pins on the base address.
 *
 * @param base Base address to GPIO addresses.
 * @param mask Specifies which pin should be set to high.
 ******************************************************************************/
static inline void GPIO_setPinsOutput(GPIO_Type* base, uint32_t mask)
{
    base->PSOR = mask;
}

/***************************************************************************//**
 * @brief Clears the output of all GPIO pins on the base address.
 *
 * @param base Base address to GPIO addresses.
 * @param mask Specifies which pin should be set to ground.
 ******************************************************************************/
static inline void GPIO_clearPinsOutput(GPIO_Type* base, uint32_t mask)
{
    base->PCOR = mask;
}

/***************************************************************************//**
 * @brief Toggles the output of all GPIO pins on the base address.
 *
 * @param base Base address to GPIO addresses.
 * @param mask Specifies which pin should be toggled.
 ******************************************************************************/
static inline void GPIO_togglePinsOutput(GPIO_Type* base, uint32_t mask)
{
    base->PTOR = mask;
}

/***************************************************************************//**
 * @brief Reads the input of the GPIO pin.
 *
 * @param base Base address to GPIO addresses.
 * @param pin Pin number (must include the offset to the base address).
 * @return
 *     @retval 1 For high input
 *     @retval 0 For ground.
 ******************************************************************************/
static inline uint8_t GPIO_readPinInput(GPIO_Type* base, uint32_t pin)
{
    return (((base->PDIR) >> pin) & 0x01u);
}

/** @} *//* end group */

