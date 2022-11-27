/*
 * global.h
 *
 *  Created on: Nov 27, 2022
 *      Author: Cao Tien Dat
 */
#include "main.h"

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define no_of_timers 4
#define no_of_btn 3

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET


//LED SCAN
int led_scan_counter = 0;

#endif /* INC_GLOBAL_H_ */
