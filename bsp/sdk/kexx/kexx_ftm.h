/** @file
 *  @defgroup FTM FTM Driver
 *  @ingroup KEXX
 *  @brief FTM driver implementation
 */

#pragma once

/** addtogroup FTM
 *  @{ */

#include <mcu.h>

/** @brief Describes the flex-timer mode.
 *
 *  Currently only the edge aligned PWM mode is implemented. */
typedef enum
{
    kFTM_MODE_NOTUSED = 0U,                              /**< Disables the module. */
    kFTM_MODE_INPUT_CAPTURE_RISING_EDGE_ONLY = 1U,       /**< Input capture mode, capture on rising edge. */
    kFTM_MODE_INPUT_CAPTURE_FALLING_EDGE_ONLY = 2U,      /**< Input capture mode, capture on falling edge. */
    kFTM_MODE_INPUT_CAPTURE_RISING_OR_FALLING_EDGE = 3U, /**< Input capture mode, capture on any edge. */
    kFTM_MODE_OUTPUT_COMPARE_TOGGLE = 5U,                /**< Output compare mode, toggle output on match. */
    kFTM_MODE_OUTPUT_COMPARE_CLEAR = 6U,                 /**< Output compare mode, clear output on match. */
    kFTM_MODE_OUTPUT_COMPARE_SET = 7U,                   /**< Output compare more, set output on match. */
    kFTM_MODE_EDGE_ALIGNED_PWM_HIGH_TRUE = 10U,          /**< Edge aligned PWM mode, high-true pulses. */
    kFTM_MODE_EDGE_ALIGNED_PWM_LOW_TRUE = 11U,           /**< Edge aligned PWM mode, low-true pulses. */
    kFTM_MODE_CENTER_ALIGNED_PWM_HIGH_TRUE = 18U,        /**< Center aligned PWM mode, high-true pulses. */
    kFTM_MODE_CENTER_ALIGNED_PWM_LOW_TRUE = 19U,         /**< Center aligned PWM mode, low-true pulses. */
    kFTM_MODE_COMBINE_PWM_HIGH_TRUE = 34U,               /**< Combine PWM mode, high-true pulses. */
    kFTM_MODE_COMBINE_PWM_LOW_TRUE = 35U,                /**< Combine PWM mode, low-true pulses. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_ONE_SHOT_NO_EDGE = 64U,  /**< Dual edge capture mode, one-shot capture, no edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_ONE_SHOT_RISING_EDGE = 65U,                /**< Dual edge capture mode, one-shot capture, rising edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_ONE_SHOT_FALLING_EDGE = 66U,               /**< Dual edge capture mode, one-shot capture, falling edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_ONE_SHOT_RISING_AND_FALLING_EDGES = 67U,   /**< Dual edge capture mode, one-shot capture, any edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_CONTINUOUS_NO_EDGE = 68U,                  /**< Dual edge capture, continuous mode, no edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_CONTINUOUS_RISING_EDGE = 69U,              /**< Dual edge capture, continuous mode, rising edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_CONTINUOUS_FALLING_EDGE = 70U,             /**< Dual edge capture, continuous mode, falling edge. */
    kFTM_MODE_DUAL_EDGE_CAPTURE_CONTINUOUS_RISING_AND_FALLING_EDGES = 71U, /**< Dual edge capture, continuous mode, any edge. */
} ftmMode_t;

/** @brief Description of the FTM module. This is not very generic, but quite specific to the edge aligned PWM mode.. */
typedef struct
{
    FTM_Type* Base;   /**< Base address to the FTM module. */
    uint32_t Channel; /**< Channel for PWM mode. */
    ftmMode_t Mode;   /**< Mode for the FTM module. */
    uint16_t Period;  /**< Period modulus, controls frequency and resolution of the pulse width. */
} ftmModule_t;

/** @brief Enables clock to FTM module.
 *  @param mod Description of the FTM module. */
static inline void ftmClockEnable(const ftmModule_t* mod){
    switch( (uint32_t) mod->Base ){
    case FTM0_BASE:
        SIM->SCGC |= SIM_SCGC_FTM0_MASK; break;
    case FTM1_BASE:
        SIM->SCGC |= SIM_SCGC_FTM1_MASK; break;
    case FTM2_BASE:
        SIM->SCGC |= SIM_SCGC_FTM2_MASK; break;
    }
}

/** @brief Disables clock to FTM module.
 *  @param mod Description of the FTM module. */
static inline void ftmClockDisable(const ftmModule_t* mod){
    switch( (uint32_t) mod->Base ){
    case FTM0_BASE:
        SIM->SCGC &= ~SIM_SCGC_FTM0_MASK; break;
    case FTM1_BASE:
        SIM->SCGC &= ~SIM_SCGC_FTM1_MASK; break;
    case FTM2_BASE:
        SIM->SCGC &= ~SIM_SCGC_FTM2_MASK; break;
    }
}

/** @brief Initialises the FTM module to the given description.
 *  @param mod Description of the FTM module. */
static inline void ftmInit(const ftmModule_t* mod){
    /* enable clock to ftm module */
    ftmClockEnable(mod);

    /* disable counter */
    mod->Base->SC = 0x0;
    mod->Base->MOD = mod->Period; /* allow for 100% duty */
    mod->Base->CNT = 0U;
    mod->Base->CONTROLS[mod->Channel].CnSC = (((uint32_t) mod->Mode) << 2U);
    mod->Base->CONTROLS[mod->Channel].CnV = 0u; /* set to 0% duty cycle, i.e. off */

    mod->Base->SC = ((0x01 << FTM_SC_CLKS_SHIFT) & FTM_SC_CLKS_MASK) | ((0x00 << FTM_SC_PS_SHIFT) & FTM_SC_PS_MASK);

    /* set mode */
}


/** @brief Sets the PWM period modulo.
 *  @param mod Description of the FTM module.
 *  @param period Specifies the required modulo period number. */
static inline void ftmSetModulePeriod(const ftmModule_t* mod, uint16_t period){
    /* period is determined by (MOD - CNTIN + 1) */
    mod->Base->CNT = 0U;
    mod->Base->MOD = ((period << FTM_MOD_MOD_SHIFT) & FTM_MOD_MOD_MASK); /* set period */
}

/** @brief Sets the pulse width, or match value if in compare or capture mode.
 *  @param mod Description of the FTM module.
 *  @param pw Specifies the value to load to the channel. */
static inline void ftmSetChannelValue(const ftmModule_t* mod, uint16_t pw){
    mod->Base->CONTROLS[mod->Channel].CnV = (pw & FTM_CnV_VAL_MASK); /* update value */
}

/** @} *//* end group */



