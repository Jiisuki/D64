/** @file
 *  @defgroup RTC RTC Driver
 *  @ingroup KEXX
 *  @brief Real-time clock driver implementation.
 */

#pragma once

/** @addtogroup RTC
 *  @{ */

#include <mcu.h>
#include <stdint.h>

/** @brief Callback type for timeout event. */
typedef uint32_t (*RTCCallbackFcn_t)(void);

/** @brief Real-time clock source.
 *
 *  Input to the RTC prescaler. Changing clock source clears
 *  the prescaler. A reset clears clock source, i.e. external. */
typedef enum
{
    kRTC_RTCLKS_EXTERNAL = 0u, /**< External clock source. */
    kRTC_RTCLKS_LPOCLK = 1u, /**< Real-time clock source is 1 kHz. */
    kRTC_RTCLKS_ICSIRCLK = 2u, /**< Internal reference clock. */
    kRTC_RTCLKS_BUS = 3u, /**< Bus clock. */
} RTCClockSource_t;

/** @brief Real-time clock prescaler. */
typedef enum
{
    kRTC_RTCPS_OFF = 0u, /**< Off. */
    kRTC_RTCPS_1_OR_128 = 1u, /**< 1 if RTCLKS<0> = 0. */
    kRTC_RTCPS_2_OR_256 = 2u, /**< 2 if RTCLKS<0> = 0. */
    kRTC_RTCPS_4_OR_512 = 3u, /**< 4 if RTCLKS<0> = 0. */
    kRTC_RTCPS_8_OR_1024 = 4u, /**< 8 if RTCLKS<0> = 0. */
    kRTC_RTCPS_16_OR_2048 = 5u, /**< 16 if RTCLKS<0> = 0. */
    kRTC_RTCPS_32_OR_100 = 6u, /**< 32 if RTCLKS<0> = 0. */
    kRTC_RTCPS_64_OR_1000 = 7u, /**< 64 if RTCLKS<0> = 0. */
} RTCPrescaler_t;

/** @brief Real-time integration settings. */
typedef enum
{
    kRTC_RTCC_CAPTURE_BY_FTM1_1 = 1u, /**< Capture RTC overflow by FTM1, channel 1. */
    kRTC_RTCC_NO_FTM_CAPTURE = 0u, /**< Don't capture RTC overflow with FTM. */
} RTCFtmCapture_t;

/** @brief Real-time counter output pin selection. */
typedef enum
{
    kRTC_PINSEL_0 = 0u, /**< Output on PTC4. */
    kRTC_PINSEL_1 = 1u, /**< Output on PTC5. */
} RTCCounterPinsel_t;

/** @brief RTC Interrupt setting. */
typedef enum
{
    kRTC_RTIE_DISABLED = 0u, /**< Interrupt disabled. */
    kRTC_RTIE_ENABLED = 1u, /**< Interrupt enabled. */
} RTCInterrupt_t;

/** @brief RTC counter output setting. */
typedef enum
{
    kRTC_RTCO_DISABLED = 0u, /**< No pin toggle. */
    kRTC_RTCO_ENABLED = 1u, /**< Pin toggle on overflow. */
} RTCCounterOutput_t;

/** @brief Structure to hold all settings for the RTC module. */
typedef struct
{
    RTCClockSource_t clockSource; /**< Select clock source for RTC module. */
    RTCPrescaler_t clockPrescaler; /**< Setup prescaler. */
    RTCInterrupt_t irq; /**< Define if interrupt shall be used. */
    RTCFtmCapture_t ftmCapture; /**< Define if RTC overflow shall be captured by flex-timer module. */
    RTCCounterOutput_t counterOutput; /**< Define if a pin should be toggled on timeout. */
    RTCCounterPinsel_t counterPinsel; /**< Define pins for counter output, if enabled. */
    RTCCallbackFcn_t callback; /**< Defines the callback for RTC tick. */
} RTCSettings_t;

/***************************************************************************//**
 * @brief Initialises the RTC module.
 *
 * @param rtc Reference to the RTC module settings.
 * @param mod RTC modulo, specifies the timeout period.
 ******************************************************************************/
void RTC_init(const RTCSettings_t* const rtc, const uint16_t mod);

/** @} *//* end group */

