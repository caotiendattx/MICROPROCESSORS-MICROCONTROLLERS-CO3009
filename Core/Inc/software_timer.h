/*
 * software_timer.h
 *
 *  Created on: Nov 27, 2022
 *      Author: Cao Tien Dat
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#include "main.h"

#define no_of_timers 4


extern int timer_flag[no_of_timers];
extern int timer_counter[no_of_timers];

extern const int time_const;

void setTimer(int duration, int indx);

void timerRun(int indx);

#endif /* INC_SOFTWARE_TIMER_H_ */
