/** @file
 *  @brief Implementation of ADC Drivers.
 */

/** @addtogroup ADC
 *  @{ */

#include "kexx_adc.h"
#include <stdint.h>
#include <stdbool.h>

/** @brief Returns maximum unsigned value based on adc mode.
 *  @return Enumerated value of 2^(mode)-1. */
ADCIntmax_t ADC_intMax(void)
{
    uint32_t mode = ((ADC->SC3 & ADC_SC3_MODE_MASK) >> ADC_SC3_MODE_SHIFT);
    switch ((uint32_t)mode)
    {
        case kADC_MODE_8bit:
            return (kADC_INTMAX_8bit);

        case kADC_MODE_10bit:
            return (kADC_INTMAX_10bit);

        case kADC_MODE_12bit:
            return (kADC_INTMAX_12bit);

        default:
            return (kADC_INTMAX_12bit);
    }
}

/***************************************************************************//**
 * @brief Disables clock to ADC module.
 ******************************************************************************/
static inline void ADC_wait(void)
{
    SIM->SCGC &= ~SIM_SCGC_ADC_MASK;
}

/***************************************************************************//**
 * @brief Enables clock to ADC module.
 ******************************************************************************/
static inline void ADC_resume(void)
{
    SIM->SCGC |= SIM_SCGC_ADC_MASK;
}

/*----------------------------------------------------------------------------*/
void ADC_init(const ADCSettings_t* const setup)
{
    /* Enable clock to ADC. */
    SIM->SCGC |= SIM_SCGC_ADC_MASK;
    ADC->SC2 = ((setup->vRef << ADC_SC2_REFSEL_SHIFT) | ~ADC_SC2_REFSEL_MASK);
    ADC->SC3 = ((setup->modeRes << ADC_SC3_MODE_SHIFT) | (setup->clockSource << ADC_SC3_ADICLK_SHIFT) | (setup->clockDiv << ADC_SC3_ADIV_SHIFT));
    ADC->SC1 &= ~ADC_SC1_ADCO_MASK;

    /* Setup hardware trigger source. */
    if (setup->conversionTrigger == kADC_TRIGGER_HARDWARE)
    {
        ADC->SC2 |= ADC_SC2_ADTRG_MASK;
        SIM->SOPT0 |= ((SIM->SOPT0 & ~SIM_SOPT0_ADHWT_MASK) | (setup->hardwareTriggerSource << SIM_SOPT0_ADHWT_SHIFT));
    }
    else
    {
        ADC->SC2 &= ~ADC_SC2_ADTRG_MASK;
    }
}

/*----------------------------------------------------------------------------*/
void ADC_defineAnalog(const ADCPin_t* const pin, const uint8_t enabled)
{
    if (enabled == 0U)
    {
        pin->base->APCTL1 |= (1U << pin->pin); /* Disable analog input. */
    }
    else
    {
        pin->base->APCTL1 &= ~(1U << pin->pin); /* Enable analog input. */
    }
}

/*----------------------------------------------------------------------------*/
uint32_t ADC_readInput(const ADCPin_t* const pin)
{
    pin->base->SC1 = (pin->pin);
    while (!(pin->base->SC1 & ADC_SC1_COCO_MASK))
    {
        /* Wait for conversion to be completed. */
    }
    return (pin->base->R);
}

/*----------------------------------------------------------------------------*/
int32_t ADC_readInputScaled(const ADCPin_t* const pin, const int32_t scaleFactor)
{
    pin->base->SC1 = (pin->pin);
    while (!(pin->base->SC1 & ADC_SC1_COCO_MASK))
    {
        /* Wait for conversion to be completed. */
    }
    int32_t result = (((int32_t) pin->base->R * scaleFactor) / ADC_intMax());
    return (result);
}

/*----------------------------------------------------------------------------*/
 bool ADC_readMultiple(const ADCPin_t** const pins, uint32_t count, uint32_t* fifo)
 {
    if (count > 8)
    {
        /* FIFO can not hold more than 8 channels, if I understood correctly. */
        return (false);
    }

    /* Setup fifo to the number of pins. */
    uint32_t sc4 = (ADC->SC4 & ~ADC_SC4_AFDEP_MASK); /* Clear FIFO settings and backup register. */
    ADC->SC4 = (sc4 | ((count-1) << ADC_SC4_AFDEP_SHIFT)); /* Update FIFO settings based on ch. count. */

    /* Now we update SC1 register with the channels in order. */
    ADC->SC1 &= ~ADC_SC1_ADCH_MASK; /* Clear channels. */
    for (uint32_t i = 0; i < count; i++)
    {
        ADC->SC1 |= (pins[i]->pin); /* Select i:th channel */
    }

    /* The register is loaded, now wait until fifo is full. */
    while (!(ADC->SC2 & ADC_SC2_FFULL_MASK))
    {
        /* Wait for completion. */
    }

    /* Extract result to fifo buffer. */
    for (uint32_t i = 0; i < count; i++)
    {
        *(fifo+i) = (ADC->R);
    }

    return (true);
}

/** @} *//* end group */
