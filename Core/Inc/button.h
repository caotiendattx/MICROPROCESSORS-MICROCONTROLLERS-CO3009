/*
 * button.h
 *
 *  Created on: Nov 27, 2022
 *      Author: Cao Tien Dat
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define no_of_btn 3
#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET



extern int keyReg[no_of_btn][4];

extern int timerForKeyPress[no_of_btn];

extern int keyPressFlag[no_of_btn];
extern int keyHoldFlag[no_of_btn];


extern uint16_t button_map[no_of_btn];


void init_button(int indx);

void keyPress(int indx);
void keyHold(int indx);
void keyRelease(int indx);

void getKeyInput(int indx);

#endif /* INC_BUTTON_H_ */
