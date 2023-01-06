#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


#define no_of_timers 2
extern int timer_flag[no_of_timers];
extern int timer_counter[no_of_timers];
extern const int time_const;

void setTimer(int duration, int indx);

void timerRun(int indx);

#endif /* INC_SOFTWARE_TIMER_H_ */
