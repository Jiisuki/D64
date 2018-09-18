/** @file
 *  @brief Peripheral Interrupt Timer interrupt handler callbacks.
 */

/** @addtogroup PIT
 *  @{ */

#include "kexx_timer.h"

/** @name Callback handlers
 *  @{ */
PeriodicTimerCallbackFcn_t CallbackCH0 = NULL; /**< Callback for channel 0. */
PeriodicTimerCallbackFcn_t CallbackCH1 = NULL; /**< Callback for channel 1. */
/** @} */

/* Enables the PIT module globally. */
void PeriodicTimer_enableGlobal(void)
{
    /* enable clock to pit */
    SIM->SCGC |= SIM_SCGC_PIT_MASK;

    /* enable pit */
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
}

/* Disables the PIT module globally. */
void PeriodicTimer_disableGlobal(void)
{
    /* disable pit */
    PIT->MCR |= PIT_MCR_MDIS_MASK;

    /* switch off clock from pit */
    SIM->SCGC &= ~SIM_SCGC_PIT_MASK;
}

/* Enables the timer. */
void PeriodicTimer_enable(const PeriodicTimer_t* const timer)
{
    PIT->CHANNEL[timer->channel].TCTRL |= PIT_TCTRL_TEN_MASK;
}

/* Disables the timer. */
void PeriodicTimer_disable(const PeriodicTimer_t* const timer)
{
    PIT->CHANNEL[timer->channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}

/* Enables the timer and waits until it times out before it returns. */
void PeriodicTimer_wait(const PeriodicTimer_t* const timer, const uint32_t us)
{
    if (0 == us)
    {
        return; /* 0 is an invalid delay time, no point. */
    }

    /* backup registers, this is to allow reverting to interrupts after if enabled */
    uint32_t ctrlreg = PIT->CHANNEL[timer->channel].TCTRL;
    uint32_t ldvalreg = PIT->CHANNEL[timer->channel].LDVAL;

    /* disable timer and load value, then enable timer */
    PIT->CHANNEL[timer->channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[timer->channel].LDVAL = ((SystemCoreClock / 2000000) * us) - 1u;
    PIT->CHANNEL[timer->channel].TCTRL |= PIT_TCTRL_TEN_MASK;

    /* wait until timer expires */
    while (!(PIT->CHANNEL[timer->channel].TFLG))
    {
        /* wait until timer expires */
    }

    PIT->CHANNEL[timer->channel].TFLG = 0x01u;
    PIT->CHANNEL[timer->channel].TCTRL &= ~PIT_TCTRL_TEN_MASK; /* disable */

    /* reset registers */
    PIT->CHANNEL[timer->channel].LDVAL = ldvalreg;
    PIT->CHANNEL[timer->channel].TCTRL = ctrlreg;
}

/* Checks the interrupt flag on the timer. */
uint8_t PeriodicTimer_checkFlag(const PeriodicTimer_t* const timer)
{
    return (((PIT->CHANNEL[timer->channel].TFLG) & PIT_TFLG_TIF_MASK) >> PIT_TFLG_TIF_SHIFT);
}

/* Clears the interrupt flag. */
void PeriodicTimer_clearFlag(const PeriodicTimer_t* const timer)
{
    PIT->CHANNEL[timer->channel].TFLG = PIT_TFLG_TIF_MASK;
}

/* Enables timer interrupt on timeout. */
void PeriodicTimer_enableInterrupt(const PeriodicTimer_t* const timer, const uint32_t us)
{
    /* Delay time of 0 us => inf delay time. Invalid! */
    if (0 == us)
    {
        return; /* sanity check */
    }

    /* setup callback */
    if (NULL == timer->callback)
    {
        return; /* sanity check */
    }

    if (0 == timer->channel)
    {
        CallbackCH0 = timer->callback;
    }
    else
    {
        CallbackCH1 = timer->callback;
    }

    /* disable timer and clear any flags */
    PIT->CHANNEL[timer->channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[timer->channel].TFLG = PIT_TFLG_TIF_MASK;

    /* set timeout value */
    PIT->CHANNEL[timer->channel].LDVAL = ((SystemCoreClock / 2000000) * us) - 1u; /* non-calibrated */

    /* enable interrupt and timer */
    PIT->CHANNEL[timer->channel].TCTRL |= (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);

    /* enable nvic irq */
    if (0 == timer->channel)
    {
        NVIC_EnableIRQ(PIT_CH0_IRQn);
    }
    else
    {
        NVIC_EnableIRQ(PIT_CH1_IRQn);
    }
}

/* Disables timer interrupt on timeout. */
void PeriodicTimer_disableInterrupt(const PeriodicTimer_t* const timer)
{
    /* disable interrupt and disable timer */
    PIT->CHANNEL[timer->channel].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);

    if (0 == timer->channel)
    {
        NVIC_DisableIRQ(PIT_CH0_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(PIT_CH1_IRQn);
    }
}

/***************************************************************************//**
 * @brief Interrupt handler for channel 0.
 ******************************************************************************/
void PIT_CH0_IRQHandler(void)
{
    if (CallbackCH0)
    {
        CallbackCH0();
    }
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}

/***************************************************************************//**
 * @brief Interrupt handler for channel 1.
 ******************************************************************************/
void PIT_CH1_IRQHandler(void)
{
    if (CallbackCH1)
    {
        CallbackCH1();
    }
    PIT->CHANNEL[1].TFLG = PIT_TFLG_TIF_MASK;
}

/** @} *//* end group */

