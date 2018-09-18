#pragma once

#include "mcu.h"
#include "kexx_gpio.h" /* for PTx -> GPIOx defines */
#include "boardTypes.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** @name Safety switches/sensors inputs.
 *  @{ */
#define BOARD_SENSORPULSE_GPIO (PTD)
#define BOARD_SENSORPULSE_PIN  (6u + PTD_OFFSET)
/** @} */

/** @name Motor mosfet driver chip.
 *  @{ */
#define BOARD_MOTOR_SPI_BASE   (SPI1)
#define BOARD_MOTOR_SPI_PINSEL (0)
#define BOARD_MOTOR_SPI_BAUD   (1000000)
/** @} */







