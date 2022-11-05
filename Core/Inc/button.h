#ifndef __BUTTON__
#define __BUTTON__

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET


extern int key1PressFlag;
extern int key1HoldFlag;
void getKey1Input();
void key1Press();
void key1Hold();
void key1Release();

extern int key2PressFlag;
extern int key2HoldFlag;
void getKey2Input();
void key2Press();
void key2Hold();
void key2Release();


extern int key3PressFlag;
extern int key3HoldFlag;
void getKey3Input();
void key3Press();
void key3Hold();
void key3Release();
#endif
