/** @file
 *  @defgroup ADC ADC Drivers
 *  @ingroup KEXX
 *  @brief ADC driver
 */

#pragma once

/** @addtogroup ADC
 *  @{ */

#include <mcu.h>
#include <MKE06Z4.h>
#include <stdint.h>
#include <stdbool.h>

/** @brief Enumerated values for holding pre-known integer max values.
 *  @see adcMode_t */
typedef enum
{
    kADC_INTMAX_8bit  = 0xff,  /**< Maximum value for unsigned 8-bit integer. */
    kADC_INTMAX_10bit = 0x3ff, /**< Maximum value for unsigned 10-bit integer. */
    kADC_INTMAX_12bit = 0xfff, /**< Maximum value for unsigned 12-bit integer. */
} ADCIntmax_t;

/** @brief Describes ADC voltage reference source. */
typedef enum
{
    kADC_VREF_VREFH_VREFL = 0U, /**< Reference is set to VREF_H and VREF_L */
    kADC_VREF_VDDA_VSSA   = 1U, /**< Reference is set to VDD_A and VSS_A */
} ADCVref_t;

/** @brief Describes the ADC conversion mode, i.e. number of bits. */
typedef enum
{
    kADC_MODE_8bit  = 0U, /**< 8-bit mode. */
    kADC_MODE_10bit = 1U, /**< 10-bit mode. */
    kADC_MODE_12bit = 2U, /**< 12-bit mode. */
} ADCMode_t;

/** @brief Describes the ADC clock source. */
typedef enum
{
    kADC_CLOCK_SEL_BUS      = 0U, /**< BUS clock as source. */
    kADC_CLOCK_SEL_BUS_DIV2 = 1U, /**< BUS clock as source, divided by 2. */
    kADC_CLOCK_SEL_ALTCLK   = 2U, /**< ALT clock as source, that is OSC_OUT. */
    kADC_CLOCK_SEL_ADACK    = 3U, /**< ADACK clock, asynchronous ADC internal clock, available in wait modes. */
} ADCClock_t;

/** @brief Describes the clock pre-scaler. */
typedef enum
{
    kADC_CLOCK_DIV_1 = 0U, /**< Divide by 1, no pre-scaler. */
    kADC_CLOCK_DIV_2 = 1U, /**< Divide by 2. */
    kADC_CLOCK_DIV_4 = 2U, /**< Divide by 4. */
    kADC_CLOCK_DIV_8 = 3U, /**< Divide by 8. */
} ADCClockDivide_t;

/** @brief Describes the FIFO size when FIFO mode is enabled. */
typedef enum
{
    kADC_FIFO_DISABLED = 0U, /**< FIFO is disabled. */
    kADC_FIFO_2_LEVEL  = 1U, /**< FIFO can hold 2 channels. */
    kADC_FIFO_3_LEVEL  = 2U, /**< FIFO can hold 3 channels. */
    kADC_FIFO_4_LEVEL  = 3U, /**< FIFO can hold 4 channels. */
    kADC_FIFO_5_LEVEL  = 4U, /**< FIFO can hold 5 channels. */
    kADC_FIFO_6_LEVEL  = 5U, /**< FIFO can hold 6 channels. */
    kADC_FIFO_7_LEVEL  = 6U, /**< FIFO can hold 7 channels. */
    kADC_FIFO_8_LEVEL  = 7U, /**< FIFO can hold 8 channels. */
} ADCFifoDepth_t;

/** @brief Specifies hardware trigger source for ADC. */
typedef enum
{
    kADC_ADHWT_RTC_OVERFLOW = 0u, /**< Trigger on RTC overflow. */
    kADC_ADHWT_FTM0 = 1u, /**< FTM0 as hardware trigger. */
    kADC_ADHWT_FTM2_INIT = 2u, /**< FTM2 init trigger with 8-bit programmable delay. */
    kADC_ADHWT_FTM2_MATCH = 3u, /**< FTM2 match trigger with 8-bit prog. delay. */
    kADC_ADHWT_PIT0 = 4u, /**< PIT channel 0 overflow. */
    kADC_ADHWT_PIT1 = 5u, /**< PIT channel 1 overflow. */
    kADC_ADHWT_ACMP0 = 6u, /**< Analog compare out 0 as trigger. */
    kADC_ADHWT_ACMP1 = 7u, /**< Analog compare out 1 as trigger. */
} ADCHardwareTriggerSource_t;

/** @brief Describes the ADC conversion trigger. */
typedef enum
{
    kADC_TRIGGER_SOFTWARE = 0U, /**< Software trigger. */
    kADC_TRIGGER_HARDWARE = 1U, /**< Hardware trigger. */
} ADCConversionTrigger_t;

/** @brief Describes whether or not continues conversion mode should be enabled. */
typedef enum
{
    kADC_CONTINUOUS_ENABLED  = 1U, /**< Continuous mode enabled. */
    kADC_CONTINUOUS_DISABLED = 0U, /**< Continuous mode disabled. */
} ADCContinuousConversion_t;

/** @brief Enumeration of special channels, if not one of the ADC pins. */
typedef enum
{
    kADC_INPUT_TEMPERATURE_SENSOR = 0x16, /**< Internal temperature sensor? */
    kADC_INPUT_BANDGAP = 0x17,            /**< Internal bandgap reference. */
    kADC_INPUT_VREFH = 0x1D,              /**< VREF_H input pin. */
    kADC_INPUT_VREFL = 0x1E,              /**< VREF_L input pin. */
    kADC_INPUT_MODULE_DISABLED = 0x1F,    /**< Selecting this will disabled the module. */
} ADCSpecialInputChannels_t;

/** @brief Description of an ADC pin. */
typedef struct
{
    ADC_Type* base; /**< Base address to the ADC module to use. */
    uint32_t pin; /**< Set's which ADC channel to use. */
} ADCPin_t;

/** @brief ADC settings structure, used to pass settings to init. */
typedef struct
{
    ADCVref_t vRef; /**< Selects reference voltage. */
    ADCMode_t modeRes; /**< Selects adc mode, i.e. resolution bits. */
    ADCClock_t clockSource; /**< Selects clock source to the ADC. */
    ADCClockDivide_t clockDiv; /**< Selects clock divisor, make sure resulting clock speed is <= 1 Mhz. */
    ADCConversionTrigger_t conversionTrigger; /**< Selects conversion trigger. */
    ADCHardwareTriggerSource_t hardwareTriggerSource; /**< Selects hwt source. */
} ADCSettings_t;

/***************************************************************************//**
 * @brief Initialises the ADC module.
 *
 * @note Clock speed must be in range [0.4, 8.0] MHz in high speed mode.
 *
 * @param setup containing configuration for ADC.
 ******************************************************************************/
void ADC_init(const ADCSettings_t* const setup);

/***************************************************************************//**
 * @brief Initialises the pin for analog input.
 *
 * This function can also be used to disable analog input on a specific pin.
 *
 * @param pin Description of the pin to initialise.
 * @param enabled Used to enable or disable the pin given by the description.
 ******************************************************************************/
void ADC_defineAnalog(const ADCPin_t* const pin, const uint8_t enabled);

/***************************************************************************//**
 * @brief Function built for non-continuous mode.
 *
 * The function initialises the conversion and waits for it to complete
 * before returning the value. The ADC module needs to be initialised
 * before calling this function. Example:
 *
 * @code
 * ADCPin_t myADCpin = {
 *     .base = ADC,
 *     .pin = 10, // analog pin ADC0_S10
 * }
 * ADC_defineAnalog(&myADCpin, 1u);
 * uint32_t value = ADC_readInput(&myADCpin);
 * @endcode
 *
 * @param pin Description of the ADC pin.
 * @return 32-bit integer holding the digital readout from the channel.
 * @see ADC_init
 ******************************************************************************/
uint32_t ADC_readInput(const ADCPin_t* const pin);

/***************************************************************************//**
 * @brief Function to read adc input, and scale by resolution.
 *
 * The function only scales by the last specified mode, i.e. bits
 * resolution. That means a output value of 1.0f = VREF_H and 0.0f = VREF_L.
 * The output result can then be scaled by the provided voltage reference.
 *
 * @code
 * ADCPin_t myADCpin = {
 *     .base = ADC,
 *     .pin = 4u,
 * }
 * ADC_defineAnalog(&myADCpin, 1u);
 * int32_t mV = ADC_readInputScaled(&myADCpin, 3300); // if VREF_H = 3.3V
 * @endcode
 *
 * @param pin Description of the ADC pin.
 * @param scaleFactor The scale factor, e.g., if VREF_H is 3.3V, providing a
 *        value of 3300 gives the output in mV.
 * @return int32_t Holding the channel value, scaled according to scaleFactor.
 * @see adcInit
 ******************************************************************************/
int32_t ADC_readInputScaled(const ADCPin_t* const pin, const int32_t scaleFactor);

/***************************************************************************//**
 * @brief Function to read multiple channels using fifo buffering.
 *
 * The function will read several channels once and output into provided buffer.
 * Example:
 *
 * @code
 * ADCPin_t* pins[4] = {&pin1, &pin2, &pin3, &pin4};
 * uint32_t outFIFO[4];
 * ADC_readMultiple(&pins, 4, outFIFO);
 * @endcode
 *
 * @param pins An array of pointers to adc pins.
 * @param count Number of pins.
 * @param fifo Pointer to an array where to store the conversion results.
 * @return
 *     @retval true If successful
 *     @retval false If count exceeds fifo depth.
 ******************************************************************************/
 bool ADC_readMultiple(const ADCPin_t** const pins, uint32_t count, uint32_t* fifo);

/***************************************************************************//**
 * @brief Returns maximum unsigned value based on adc mode.
 * @return Enumerated value of 2^(mode)-1.
 ******************************************************************************/
ADCIntmax_t ADC_intMax(void);

/** @} *//* end group */
