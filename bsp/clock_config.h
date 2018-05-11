#pragma once

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ 8000000U /*!< Board xtal0 frequency in Hz */

/** @brief This function executes default configuration of clocks. */
void BOARD_InitBootClocks(void);

#define BOARD_BOOTCLOCKRUN_CORE_CLOCK 40000000U /*!< Core clock frequency: 40000000Hz */

/** @brief ICS set for BOARD_BootClockRUN configuration. */
extern const ics_config_t icsConfig_BOARD_BootClockRUN;

/** @brief SIM module set for BOARD_BootClockRUN configuration. */
extern const sim_clock_config_t simConfig_BOARD_BootClockRUN;

/** @brief OSC set for BOARD_BootClockRUN configuration. */
extern const osc_config_t oscConfig_BOARD_BootClockRUN;

/** @brief This function executes configuration of clocks. */
void BOARD_BootClockRUN(void);

