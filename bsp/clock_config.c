#include "clock_config.h"

/* System clock frequency. */
extern uint32_t SystemCoreClock;

void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

const ics_config_t icsConfig_BOARD_BootClockRUN = {
    .icsMode = kICS_ModeFEE,             /* FEE - FLL Engaged External */
    .irClkEnableMode = kICS_IrclkEnable, /* ICSIRCLK enabled, ICSIRCLK disabled in STOP mode */
    .bDiv = 0x0U,                        /* Bus clock divider: divided by 1 */
    .rDiv = 0x3U,                        /* FLL external reference clock divider: divided by 256 */
};

const sim_clock_config_t simConfig_BOARD_BootClockRUN = {
    .outDiv1 = 0x0U,         /* DIV1 clock divider: divided by 1 */
    .outDiv2 = 0x1U,         /* DIV2 clock divider: divided by 2 */
    .outDiv3 = 0x0U,         /* DIV3 clock divider: divided by 1 */
    .busClkPrescaler = 0x0U, /* bus clock optional prescaler */
};

const osc_config_t oscConfig_BOARD_BootClockRUN = {
    .freq = 8000000U,                 /* Oscillator frequency: 8000000Hz */
    .workMode = kOSC_ModeOscLowPower, /* Oscillator low power */
    .enableMode = kOSC_Enable, /* Enable external reference clock, disable external reference clock in STOP mode */
};

void BOARD_BootClockRUN(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_BOARD_BootClockRUN);
    CLOCK_SetXtal0Freq(oscConfig_BOARD_BootClockRUN.freq);
    /* Set ICS to FEE mode. */
    CLOCK_BootToFeeMode(icsConfig_BOARD_BootClockRUN.bDiv, icsConfig_BOARD_BootClockRUN.rDiv);
    /* Configure the Internal Reference clock (ICSIRCLK). */
    CLOCK_SetInternalRefClkConfig(icsConfig_BOARD_BootClockRUN.irClkEnableMode);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}
