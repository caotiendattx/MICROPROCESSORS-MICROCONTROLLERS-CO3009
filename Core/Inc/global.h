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




//FSM
int current_fsm_state = 0;
#define NORMAL_MODE 0
#define MODE_2 	1
#define MODE_3 	2
#define MODE_4 	3
//LED SCAN
int led_scan_counter = 0;

int traffic_state = 0;

int time_red = 1000;
int time_yellow = 300;
int time_green = 700;
#endif /* INC_GLOBAL_H_ */
