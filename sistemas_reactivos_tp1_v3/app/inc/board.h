/*
 * board.h
 *
 *  Created on: Jul 6, 2025
 *      Author: HP VICTUS
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "stm32f4xx_hal.h"

#define BUTTON_PORT     GPIOC
#define BUTTON_PIN      GPIO_PIN_13

#define LED_RED_PORT    GPIOB
#define LED_RED_PIN     GPIO_PIN_0

#define LED_GREEN_PORT  GPIOB
#define LED_GREEN_PIN   GPIO_PIN_7

#define LED_BLUE_PORT   GPIOB
#define LED_BLUE_PIN    GPIO_PIN_14

#endif /* BOARD_H_ */
