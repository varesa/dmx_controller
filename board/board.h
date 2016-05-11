/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
//#define BOARD_ST_NUCLEO_F103RB
#define BOARD_NAME              "Taita2016 DMX Controller"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            0
#define STM32_HSECLK            25000000


/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#ifndef STM32F103xB
#define STM32F103xB
#endif

/*
 * IO pins assignments.
 */
#define GPIOA_PA0               0
#define GPIOA_PA1               1
#define GPIOA_PA2               2
#define GPIOA_PA3               3
#define GPIOA_PA4               4
#define GPIOA_PA5               5
#define GPIOA_PA6               6
#define GPIOA_PA7               7
#define GPIOA_PA8               8
#define GPIOA_PA9               9
#define GPIOA_PA10              10
#define GPIOA_PA11              11
#define GPIOA_PA12              12
#define GPIOA_SWDIO             13
#define GPIOA_SWCLK             14
#define GPIOA_PA15              15

#define GPIOB_PB0               0
#define GPIOB_PB1               1
#define GPIOB_PB2               2
#define GPIOB_SWO               3
#define GPIOB_PB4               4
#define GPIOB_PB5               5
#define GPIOB_PB6               6
#define GPIOB_PB7               7
#define GPIOB_PB8               8
#define GPIOB_PB9               9
#define GPIOB_PB10              10
#define GPIOB_PB11              11
#define GPIOB_PB12              12
#define GPIOB_PB13              13
#define GPIOB_PB14              14
#define GPIOB_PB15              15

#define GPIOC_PC0               0
#define GPIOC_PC1               1
#define GPIOC_PC2               2
#define GPIOC_PC3               3
#define GPIOC_PC4               4
#define GPIOC_PC5               5
#define GPIOC_PC6               6
#define GPIOC_PC7               7
#define GPIOC_PC8               8
#define GPIOC_PC9               9
#define GPIOC_PC10              10
#define GPIOC_PC11              11
#define GPIOC_PC12              12
#define GPIOC_PC13              13
#define GPIOC_PC14              14
#define GPIOC_PC15              15

#define GPIOD_OSC_IN            0
#define GPIOD_OSC_OUT           1
#define GPIOD_PD2               2

/*
 * Custom IO labels
 */

// Status LED

#define GPIO_LED GPIOA_PA6

// LCD

#define LCD_RS GPIOC_PC13
#define LCD_RW GPIOC_PC14
#define LCD_E  GPIOC_PC15

#define LCD_CTRL_GPIO GPIOC

#define LCD_D0 GPIOB_PB8
#define LCD_D1 GPIOB_PB9
#define LCD_D2 GPIOB_PB10
#define LCD_D3 GPIOB_PB11
#define LCD_D4 GPIOB_PB12
#define LCD_D5 GPIOB_PB13
#define LCD_D6 GPIOB_PB14
#define LCD_D7 GPIOB_PB15

#define LCD_DATA_GPIO GPIOB
#define LCD_DATA_MASK
#define LCD_DATA_OFFSET 8

// Buttons

#define BTN_UP      GPIOB_PB4
#define BTN_LEFT    GPIOB_PB7
#define BTN_RIGHT   GPIOB_PB5
#define BTN_DOWN    GPIOB_PB6

#define BTN_DIR_GPIO GPIOB

#define BTN_1   GPIOB_PB0
#define BTN_2   GPIOB_PB1
#define BTN_3   GPIOB_PB2
#define BTN_4   GPIOA_PA5
#define BTN_5   GPIOA_PA7

#define BTN_123_GPIO GPIOB
#define BTN_45_GPIO GPIOA

/*
 * Other labels
 */

#define SPI_ENC             &SPID1


/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 *
 * PA0-PA4   * Analog inputs
 * PA5       * Digital input   (BTN)
 * PA6 LED   * Digital output, P-P 2MHz (LED)
 * PA7       * Digital input   (BTN)
 *
 * PA8       * Digital input (unused)
 * PA9       * AF P-P 10MHz
 * PA10-PA15 * Digital input (Unused/SWD)
 */
#define VAL_GPIOACRL            0x82800000      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x88888898      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
 *
 * PB0-PB2  * Digital input (BTN)
 * PB3      * SWO
 * PB4-PB7  * Digital input (BTN)
 *
 * PB8-PB15 * Digital output, P-P 2MHz
 */
#define VAL_GPIOBCRL            0x88888888      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x22222222      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 *
 * PC0-PC7   * Not on chip
 *
 * PC8-PC12  * Not on chip
 * PC13-PC15 * Digital output, P-P 2MHz
 */
#define VAL_GPIOCCRL            0x88888888      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x22288888      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Not on chip
 */
#define VAL_GPIODCRL            0x88888888      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Not on chip
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
