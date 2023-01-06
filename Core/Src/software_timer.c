#include "software_timer.h"

int timer_flag[no_of_timers] = {0};
int timer_counter[no_of_timers] = {0};
const int time_const = 1;

void setTimer(int duration, int indx)
{
	timer_counter[indx] = duration/time_const;
	timer_flag[indx] = 0;
}

void timerRun(int indx)
{
	if(timer_counter[indx] > 0)
	{
		timer_counter[indx]--;
		if(timer_counter[indx] == 0)
		{
			timer_flag[indx] = 1;
		}
	}
	else timer_flag[indx] = 1;
}
