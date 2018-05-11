/*
 * application.c
 *
 *  Created on: 10 May 2018
 *      Author: Jiisuki
 */

#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"

int main(void)
{
    BOARD_InitBootClocks();
    BOARD_InitBootPins();
    BOARD_InitBootPeripherals();


    // Bootup

    BOARD_InitOSC();
}
