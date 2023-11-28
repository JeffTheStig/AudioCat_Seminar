/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/
#define PA0                     0
#define PA1                     1
#define PA2                     2
#define PA3                     3
#define PA4                     PIN_A4
#define PA5                     PIN_A5
#define PA6                     PIN_A6
#define PA7                     PIN_A7
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PA15                    15
#define PB0                     16
#define PB1                     17
#define PB2                     18
#define PB3                     19
#define PB4                     20
#define PB5                     21
#define PB6                     22
#define PB7                     23
#define PB8                     24
#define PB9                     25
#define PB10                    26
#define PB11                    27
#define PB13                    28
#define PB14                    29
#define PB15                    30
#define PC0                     31
#define PC1                     32
#define PC2                     33
#define PC3                     PIN_A14
#define PC6                     35
#define PC7                     36
#define PC8                     37
#define PC9                     38
#define PC10                    39
#define PC11                    40
#define PC12                    41
#define PC13                    42
#define PC14                    43
#define PC15                    44
#define PD0                     45
#define PD1                     46
#define PD2                     47
#define PD3                     48
#define PD4                     49
#define PD5                     50
#define PD6                     51
#define PD7                     52
#define PD8                     53
#define PD9                     54
#define PD10                    55
#define PD11                    56
#define PD12                    57
#define PD13                    58
#define PD14                    59
#define PD15                    60
#define PE0                     61
#define PE1                     62
#define PE2                     63
#define PE3                     64
#define PE4                     65
#define PE5                     66
#define PE6                     67
#define PE7                     68
#define PE8                     69
#define PE9                     70
#define PE10                    71
#define PE11                    72
#define PE12                    73
#define PE13                    74
#define PE14                    75
#define PE15                    76
#define PF0                     77
#define PF1                     78
#define PF2                     79
#define PF3                     80
#define PF4                     81
#define PF5                     82
#define PF6                     83
#define PF7                     84
#define PF8                     85
#define PF9                     86
#define PF10                    87
#define PF11                    88
#define PF12                    89
#define PF13                    90
#define PF14                    91
#define PF15                    92
#define PG0                     93
#define PG1                     94
#define PG2                     95
#define PG3                     96
#define PG4                     97
#define PG5                     98
#define PG6                     99
#define PG7                     100
#define PG8                     101
#define PG9                     102
#define PG10                    103
#define PG12                    104
#define PG13                    105
#define PG14                    106
#define PG15                    107
#define PH0                     108
#define PH1                     109
#define PH3                     110

// Alternate pins number
#define PA4_ALT1                (PA4  | ALT1)
#define PA4_ALT2                (PA4  | ALT2)
#define PA5_ALT1                (PA5  | ALT1)
#define PA5_ALT2                (PA5  | ALT2)
#define PA6_ALT1                (PA6  | ALT1)
#define PA6_ALT2                (PA6  | ALT2)
#define PA7_ALT1                (PA7  | ALT1)
#define PA7_ALT2                (PA7  | ALT2)
#define PC3_ALT1                (PC3  | ALT1)
#define PC3_ALT2                (PC3  | ALT2)

#define NUM_DIGITAL_PINS        111
#define NUM_ANALOG_INPUTS       22

// On-board LED pin number
#ifndef LED_BUILTIN
  #define LED_BUILTIN           PG3
  #define MCU_LED2              PG3
  #define MCU_LED1              PG4
#endif

// On-board user button
#ifndef USER_BTN
  #define USER_BTN              PG2
  #define MCU_BTN1              PG2
#endif

// SPI definitions
#ifndef PIN_SPI_SS
  #define PIN_SPI_SS            PG12
#endif
#ifndef PIN_SPI_MOSI
  #define PIN_SPI_MOSI          PD6
#endif
#ifndef PIN_SPI_MISO
  #define PIN_SPI_MISO          PG10
#endif
#ifndef PIN_SPI_SCK
  #define PIN_SPI_SCK           PG9
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
  #define PIN_WIRE_SDA          PC1
#endif
#ifndef PIN_WIRE_SCL
  #define PIN_WIRE_SCL          PC0
#endif

// // Timer Definitions
// // Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
// #ifndef TIMER_TONE
//   #define TIMER_TONE            TIM6
// #endif
// #ifndef TIMER_SERVO
//   #define TIMER_SERVO           TIM7
// #endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  4
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
  #define PIN_SERIAL_RX         PA1
#endif
#ifndef PIN_SERIAL_TX
  #define PIN_SERIAL_TX         PA0
#endif

// Extra HAL modules
// #if !defined(HAL_DAC_MODULE_DISABLED)
//   #define HAL_DAC_MODULE_ENABLED
// #endif
// #if !defined(HAL_OSPI_MODULE_DISABLED)
//   #define HAL_OSPI_MODULE_ENABLED
// #endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif

#define SD_FET_EN             PE3
#define SRAM_FET_EN           PE2
#define GPS_FET_EN            PE0
#define RADIO_FET_EN          PB4
#define MIC_US_FET_EN         PB0
#define OPAMP_LP_FET_EN       PD13
#define BMI088_FET_EN         PC2
#define BME688_FET_EN         PB10
#define BH1749NUC_FET_EN      PB1
#define LDO_1V0_EN            PA3

#define MIC_US_OUT            PA5
#define MIC_LP_OUT            PA4
#define MIC_LP_OUT_ALT        PC3

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif