/** @file
 *  @defgroup RTC RTC Driver
 *  @ingroup KEXX
 *  @brief RTC Irq callback handler.
 */

/** @addtogroup RTC
 *  @{ */

#include <kexx_rtc.h>
#include <mcu.h>
#include <stdlib.h>

/** @brief Callback handler */
RTCCallbackFcn_t rtcCallback = NULL;

/* Initialise the RTC. */
void RTC_init(const RTCSettings_t* const rtc, const uint16_t mod)
{
    /* enable clock to rtc */
    SIM->SCGC |= SIM_SCGC_RTC_MASK;
    RTC->SC = (rtc->clockSource << RTC_SC_RTCLKS_SHIFT) |
              (rtc->clockPrescaler << RTC_SC_RTCPS_SHIFT) |
              (rtc->counterOutput << RTC_SC_RTCO_SHIFT);

    /* define callback, if defined. */
    if (rtc->callback)
    {
        rtcCallback = rtc->callback;
    }

    /* setup irq. */
    if (kRTC_RTIE_ENABLED == rtc->irq)
    {
        RTC->SC |= (RTC_SC_RTIE_MASK | RTC_SC_RTIF_MASK);
        NVIC_EnableIRQ(RTC_IRQn);
    }
    else
    {
        RTC->SC &= ~RTC_SC_RTIE_MASK;
        NVIC_DisableIRQ(RTC_IRQn);
    }

    /* counter output pinsel */
    if (kRTC_PINSEL_0 == rtc->counterPinsel)
    {
        SIM->PINSEL &= ~SIM_PINSEL_RTCPS_MASK;
    }
    else
    {
        SIM->PINSEL |= SIM_PINSEL_RTCPS_MASK;
    }

    /* ftm capture mode */
    if (kRTC_RTCC_CAPTURE_BY_FTM1_1 == rtc->ftmCapture)
    {
        SIM->SOPT0 |= SIM_SOPT0_RTCC_MASK;
    }
    else
    {
        SIM->SOPT0 &= ~SIM_SOPT0_RTCC_MASK;
    }

    /* setup modulo. */
    RTC->MOD = (mod - 1);
}

/** @brief RTC Irq request handler. */
void RTC_IRQHandler(void)
{
    if (rtcCallback)
    {
        rtcCallback();
    }

    RTC->SC |= RTC_SC_RTIF_MASK; /* clear flag */
}

/** @} *//* end group */

