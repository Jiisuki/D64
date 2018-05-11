/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.0
processor: MKE06Z128xxx4
package_id: MKE06Z128VLK4
mcu_data: ksdk2_0
processor_version: 0.0.8
board: FRDM-KE06Z
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "pin_mux.h"
#include "fsl_common.h"
#include "fsl_port.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDs:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '50', peripheral: GPIOB, signal: 'GPIO, 23', pin_signal: PTG7/KBI1_P23/FTM2_CH5/SPI1_PCS}
  - {pin_num: '51', peripheral: GPIOB, signal: 'GPIO, 22', pin_signal: PTG6/KBI1_P22/FTM2_CH4/SPI1_MISO}
  - {pin_num: '52', peripheral: GPIOB, signal: 'GPIO, 21', pin_signal: PTG5/KBI1_P21/FTM2_CH3/SPI1_MOSI}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDs(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UART:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '64', peripheral: UART1, signal: RX, pin_signal: PTC6/KBI0_P22/UART1_RX/CAN0_RX}
  - {pin_num: '63', peripheral: UART1, signal: TX, pin_signal: PTC7/KBI0_P23/UART1_TX/CAN0_TX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UART
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UART(void)
{
    /* pin 64,63 is configured as UART1_RX, UART1_TX */
    PORT_SetPinSelect(kPORT_UART1, kPORT_UART1_RXPTC7_TXPTC6);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCEL:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '59', peripheral: I2C0, signal: SCL, pin_signal: PTA3/KBI0_P3/UART0_TX/I2C0_SCL}
  - {pin_num: '60', peripheral: I2C0, signal: SDA, pin_signal: PTA2/KBI0_P2/UART0_RX/I2C0_SDA}
  - {pin_num: '56', peripheral: GPIOA, signal: 'GPIO, 28', pin_signal: PTD4/KBI0_P28}
  - {pin_num: '57', peripheral: GPIOA, signal: 'GPIO, 27', pin_signal: PTD3/KBI0_P27/SPI1_PCS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCEL
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCEL(void)
{
    /* pin 59,60 is configured as I2C0_SCL, I2C0_SDA */
    PORT_SetPinSelect(kPORT_I2C0, kPORT_I2C0_SCLPTA3_SDAPTA2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSC:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '13', peripheral: OSC, signal: EXTAL, pin_signal: PTB7/KBI0_P15/I2C0_SCL/EXTAL}
  - {pin_num: '14', peripheral: OSC, signal: XTAL, pin_signal: PTB6/KBI0_P14/I2C0_SDA/XTAL}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSC
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSC(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitCAN:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '6', peripheral: MSCAN, signal: TX, pin_signal: PTE7/KBI1_P7/TCLK2/FTM1_CH1/CAN0_TX}
  - {pin_num: '7', peripheral: MSCAN, signal: RX, pin_signal: PTH2/KBI1_P26/BUSOUT/FTM1_CH0/CAN0_RX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitCAN
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitCAN(void)
{
    /* pin 6,7 is configured as CAN0_TX, CAN0_RX */
    PORT_SetPinSelect(kPORT_MSCAN, kPORT_MSCAN_TXPTE7_RXPTH2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitINFRARED:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '41', peripheral: GPIOA, signal: 'GPIO, 9', pin_signal: PTB1/KBI0_P9/UART0_TX/ADC0_SE5}
  - {pin_num: '61', peripheral: GPIOA, signal: 'GPIO, 1', pin_signal: PTA1/KBI0_P1/FTM0_CH1/I2C0_4WSDAOUT/ACMP0_IN1/ADC0_SE1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitINFRARED
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitINFRARED(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitTHER:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '38', peripheral: ADC, signal: 'SE, 12', pin_signal: PTF4/KBI1_P12/ADC0_SE12}
  - {pin_num: '37', peripheral: ADC, signal: 'SE, 13', pin_signal: PTF5/KBI1_P13/ADC0_SE13}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitTHER
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitTHER(void)
{
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
