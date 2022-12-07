
#include "button.h"





int keyReg[no_of_btn][4];

int timerForKeyPress[no_of_btn];

int keyPressFlag[no_of_btn] = {0};
int keyHoldFlag[no_of_btn] = {0};


uint16_t button_map[no_of_btn] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};


void init_button(int indx)
{
	keyPressFlag[indx] = 0;
	keyHoldFlag[indx] = 0;
	timerForKeyPress[indx] = 0;
	keyReg[indx][0] = NORMAL_STATE;
	keyReg[indx][1] = NORMAL_STATE;
	keyReg[indx][2] = NORMAL_STATE;
	keyReg[indx][3] = NORMAL_STATE;
}


void keyPress(int indx)
{
	keyPressFlag[indx] = 1;
}
void keyHold(int indx)
{
	keyHoldFlag[indx] = 1;
}
void keyRelease(int indx)
{
	timerForKeyPress[indx] = 0;
	keyHoldFlag[indx] = 0;
}

void getKeyInput(int indx)
{
	keyReg[indx][0] = keyReg[indx][1];
	keyReg[indx][1] = keyReg[indx][2];
	keyReg[indx][2] = HAL_GPIO_ReadPin(btn1_GPIO_Port, button_map[indx]);
	// Only care about non-bounce
	if((keyReg[indx][0] == keyReg[indx][1]) && (keyReg[indx][1] == keyReg[indx][2]))
	{
		if((keyReg[indx][3] == NORMAL_STATE) && (keyReg[indx][1]  == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Released then Pressed
		{
			keyReg[indx][3] = keyReg[indx][2];
			timerForKeyPress[indx] = 2; //
		}
		else if((keyReg[indx][3] == PRESSED_STATE) && (keyReg[indx][1] == NORMAL_STATE))// Case: In the last 40ms, Read 2 accepted action: Pressed then Released
		{
			keyReg[indx][3] = keyReg[indx][2];
			if(timerForKeyPress[indx] < 300)
			{
				keyPress(indx);
				timerForKeyPress[indx] = 0;
			}
			else
			{
				keyRelease(indx);
				timerForKeyPress[indx] = 0;
			}
		}
		else if((keyReg[indx][3] == PRESSED_STATE) && (keyReg[indx][1] == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Pressed then Pressed
		{
			keyReg[indx][3] = keyReg[indx][2];
			timerForKeyPress[indx]++;
			if(timerForKeyPress[indx] >= 300)
			{
				keyHold(indx);
			}
		}
		else //Case: In the last 40ms, Read 2 accepted action: Released then Released
		{
			keyReg[indx][3] = keyReg[indx][2];
			timerForKeyPress[indx] = 0;
			keyHoldFlag[indx] = 0;
			keyPressFlag[indx] = 0;
		}
	}
}

