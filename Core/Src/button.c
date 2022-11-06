#include "button.h"
#include "global.h"


int key1Reg0 = NORMAL_STATE;
int key1Reg1 = NORMAL_STATE;
int key1Reg2 = NORMAL_STATE;

int key1Reg3 = NORMAL_STATE;
int timerForKey1Press = 0;

int key1PressFlag = 0;
int key1HoldFlag = 0;

void key1Press()
{
	key1PressFlag = 1;
}
void key1Hold()
{
	key1HoldFlag = 1;
}
void key1Release()
{
	timerForKey1Press = 0;
	key1HoldFlag = 0;
}

void getKey1Input()
{
	key1Reg0 = key1Reg1;
	key1Reg1 = key1Reg2;
	key1Reg2 = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	// Only care about non-bounce
	if((key1Reg0 == key1Reg1) && (key1Reg1 == key1Reg2))
	{
		if((key1Reg3 == NORMAL_STATE) && (key1Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Released then Pressed
		{
			key1Reg3 = key1Reg2;
			timerForKey1Press = 2; //
		}
		else if((key1Reg3 == PRESSED_STATE) && (key1Reg1 == NORMAL_STATE))// Case: In the last 40ms, Read 2 accepted action: Pressed then Released
		{
			key1Reg3 = key1Reg2;
			if(timerForKey1Press < 300)
			{

				key1Press();
				timerForKey1Press = 0;
			}
			else
			{
				key1Release();
				timerForKey1Press = 0;
			}
		}
		else if((key1Reg3 == PRESSED_STATE) && (key1Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Pressed then Pressed
		{
			key1Reg3 = key1Reg2;
			timerForKey1Press++;
			if(timerForKey1Press >= 300)
			{
				key1Hold();
			}
		}
		else //Case: In the last 40ms, Read 2 accepted action: Released then Released
		{
			key1Reg3 = key1Reg2;
			timerForKey1Press = 0;
			key1HoldFlag = 0;
			key1PressFlag = 0;
		}
	}
}

//////////////////////////////////////////////////////////////
int key2Reg0 = NORMAL_STATE;
int key2Reg1 = NORMAL_STATE;
int key2Reg2 = NORMAL_STATE;

int key2Reg3 = NORMAL_STATE;
int timerForKey2Press = 0;

int key2PressFlag = 0;
int key2HoldFlag = 0;

void key2Press()
{
	key2PressFlag = 1;
}
void key2Hold()
{
	Led7SegDisplayValue++;
	if(Led7SegDisplayValue > 9){Led7SegDisplayValue=0;}
	key2HoldFlag = 1;
	setTimer4(100);
}
void key2Release()
{
	timerForKey2Press = 0;
	key2HoldFlag = 0;
}

void getKey2Input()
{
	key2Reg0 = key2Reg1;
	key2Reg1 = key2Reg2;
	key2Reg2 = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
	// Only care about non-bounce
	if((key2Reg0 == key2Reg1) && (key2Reg1 == key2Reg2))
	{
		if((key2Reg3 == NORMAL_STATE) && (key2Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Released then Pressed
		{
			key2Reg3 = key2Reg2;
			timerForKey2Press = 2; //
		}
		else if((key2Reg3 == PRESSED_STATE) && (key2Reg1 == NORMAL_STATE))// Case: In the last 40ms, Read 2 accepted action: Pressed then Released
		{
			key2Reg3 = key2Reg2;
			if(timerForKey2Press < 300)
			{

				key2Press();
				timerForKey2Press = 0;
			}
			else
			{
				key2Release();
				timerForKey2Press = 0;
			}
		}
		else if((key2Reg3 == PRESSED_STATE) && (key2Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Pressed then Pressed
		{
			key2Reg3 = key2Reg2;
			timerForKey2Press++;
			if(timerForKey2Press >= 300)
			{
				if(!key2HoldFlag)
				{key2Hold();}
			}
		}
		else //Case: In the last 40ms, Read 2 accepted action: Released then Released
		{
			key2Reg3 = key2Reg2;
			timerForKey2Press = 0;
			key2HoldFlag = 0;
			key2PressFlag = 0;
		}
	}
}

///////////////////////////////////////////////////
int key3Reg0 = NORMAL_STATE;
int key3Reg1 = NORMAL_STATE;
int key3Reg2 = NORMAL_STATE;

int key3Reg3 = NORMAL_STATE;
int timerForKey3Press = 0;

int key3PressFlag = 0;
int key3HoldFlag = 0;

void key3Press()
{
	key3PressFlag = 1;
}
void key3Hold()
{
	Led7SegDisplayValue--;
	if(Led7SegDisplayValue < 0){Led7SegDisplayValue=9;}
	key3HoldFlag = 1;
	setTimer4(100);
}
void key3Release()
{
	timerForKey3Press = 0;
	key3HoldFlag = 0;
}

void getKey3Input()
{
	key3Reg0 = key3Reg1;
	key3Reg1 = key3Reg2;
	key3Reg2 = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
	// Only care about non-bounce
	if((key3Reg0 == key3Reg1) && (key3Reg1 == key3Reg2))
	{
		if((key3Reg3 == NORMAL_STATE) && (key3Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Released then Pressed
		{
			key3Reg3 = key3Reg2;
			timerForKey3Press = 2; //
		}
		else if((key3Reg3 == PRESSED_STATE) && (key3Reg1 == NORMAL_STATE))// Case: In the last 40ms, Read 2 accepted action: Pressed then Released
		{
			key3Reg3 = key3Reg2;
			if(timerForKey3Press < 300)
			{

				key3Press();
				timerForKey3Press = 0;
			}
			else
			{
				key3Release();
				timerForKey3Press = 0;
			}
		}
		else if((key3Reg3 == PRESSED_STATE) && (key3Reg1 == PRESSED_STATE))//Case: In the last 40ms, Read 2 accepted action: Pressed then Pressed
		{
			key3Reg3 = key3Reg2;
			timerForKey3Press++;
			if(timerForKey3Press >= 300)
			{
				if(!key3HoldFlag)
				{key3Hold();}
			}
		}
		else //Case: In the last 40ms, Read 2 accepted action: Released then Released
		{
			key3Reg3 = key3Reg2;
			timerForKey3Press = 0;
			key3HoldFlag = 0;
			key3PressFlag = 0;
		}
	}
}
