/** @file
 *  @brief 
 */

#include <stdbool.h>

#include "mcu.h"
#include "kexx_kbi.h"

#define KBI_NUM_PINS (32)

static KBICallbackFcn_t KBI0Callback = (void*) 0;
static KBICallbackFcn_t KBI1Callback = (void*) 0;

/* Local prototypes. */
static bool KBI_assert(const KBIPin_t* const pin);

bool KBI_init(KBI_Type* const base, const KBIMode_t mode, const KBICallbackFcn_t const callback)
{
    /* Enable clock to module. */
    if (KBI0 == base)
    {
        SIM->SCGC |= SIM_SCGC_KBI0_MASK;
        if (callback)
        {
            KBI0Callback = callback;
        }
    }
    else if (KBI1 == base)
    {
        SIM->SCGC |= SIM_SCGC_KBI1_MASK;
        if (callback)
        {
            KBI1Callback = callback;
        }
    }
    else
    {
        /* Error, no such module. */
        return (false);
    }

    if (KBIModeEdgeAndLevel == mode)
    {
        base->SC |= KBI_SC_KBMOD_MASK;
    }
    else
    {
        base->SC &= ~KBI_SC_KBMOD_MASK;
    }

    return (true);
}

void KBI_deInit(const KBI_Type* const base)
{
    if (KBI0 == base)
    {
        SIM->SCGC &= ~SIM_SCGC_KBI0_MASK;
    }
    else if (KBI1 == base)
    {
        SIM->SCGC &= ~SIM_SCGC_KBI1_MASK;
    }
}

void KBI_enablePin(KBIPin_t* const pin)
{
    if (!KBI_assert(pin))
    {
        return;
    }

    /* Mask keyboard interrupts. */
    pin->base->SC &= ~KBI_SC_KBIE_MASK;

    /* Setup edge. */
    if (KBIEdgeRising == pin->edge)
    {
        pin->base->ES |= (1u << pin->pin);
    }
    else
    {
        pin->base->ES &= ~(1u << pin->pin);
    }

    /** @todo Add support for selecting internal pullups? If so, add here. */

    /* Enable pin. */
    pin->base->PE |= (1u << pin->pin);

    /* Clear false interrupts. */
    pin->base->SC |= KBI_SC_KBACK_MASK;
    pin->base->SC |= KBI_SC_RSTKBSP_MASK;

    /* Enable interrupts. */
    pin->base->SC |= KBI_SC_KBIE_MASK;
}

void KBI_enableNVIC(KBIPin_t* const pin)
{
    if (KBI0 == pin->base)
    {
        NVIC_EnableIRQ(KBI0_IRQn);
    }
    else if (KBI1 == pin->base)
    {
        NVIC_EnableIRQ(KBI1_IRQn);
    }
}

void KBI_disableNVIC(KBIPin_t* const pin)
{
    if (KBI0 == pin->base)
    {
        NVIC_DisableIRQ(KBI0_IRQn);
    }
    else if (KBI1 == pin->base)
    {
        NVIC_DisableIRQ(KBI1_IRQn);
    }
}

void KBI_disablePin(KBIPin_t* const pin)
{
    /* Assert pin. */
    if (KBI_assert(pin))
    {
        pin->base->PE &= ~(1u << pin->pin);
    }
}

static bool KBI_assert(const KBIPin_t* const pin)
{
    bool result = false;

    if ((KBI0 == pin->base) || (KBI1 == pin->base))
    {
        result = true;
    }
    else
    {
        return (false);
    }

    if (pin->pin < KBI_NUM_PINS)
    {
        if (result)
        {
            return (true);
        }
    }

    return (false);
}

void KBI0_IRQHandler(void)
{
    uint32_t mask = KBI0->SP;

    /* Which pin? */
    for (uint8_t pin = 0; pin < KBI_NUM_PINS; pin++)
    {
        /** @note This is the opposite of what is stated in RM. Reset state is 1, triggered is 0. */
        if (0u == (mask & 0x01))
        {
            if (KBI0Callback)
            {
                KBI0Callback(pin);
            }
        }
        mask = (mask >> 1u);
    }

    /* Clear register. */
    KBI0->SC |= KBI_SC_KBACK_MASK;
    KBI0->SC |= KBI_SC_RSTKBSP_MASK;
}

void KBI1_IRQHandler(void)
{
    uint32_t mask = KBI1->SP;

    /* Which pin? */
    for (uint8_t pin = 0; pin < KBI_NUM_PINS; pin++)
    {
        /** @note This is the opposite of what is stated in RM. Reset state is 1, triggered is 0. */
        if (0u == (mask & 0x01))
        {
            if (KBI1Callback)
            {
                KBI1Callback(pin);
            }
        }
        mask = (mask >> 1u);
    }

    /* Clear register. */
    KBI1->SC |= KBI_SC_KBACK_MASK;
    KBI1->SC |= KBI_SC_RSTKBSP_MASK;
}
