/*
 * button.c
 *
 *  Created on: Nov 14, 2023
 *      Author: TuanAnh
 */

#include "button.h"

#define N0_OF_BUTTONS 3

int button_flag[N0_OF_BUTTONS] = {0, 0, 0};

GPIO_PinState KeyReg0[N0_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
GPIO_PinState KeyReg1[N0_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
GPIO_PinState KeyReg2[N0_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
GPIO_PinState KeyReg3[N0_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int TimerForKeyPress[N0_OF_BUTTONS] = {1000, 1000, 1000}; // hold time = n/10 (e.g <- 1s);

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	} else {
		return 0;
	}
}


void subKeyProcess(int index) {
	button_flag[index] = 1;

}

void getKeyInput() {
	for (int i = 0; i < N0_OF_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		switch (i) {
			case 0:
				KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin);
				break;
			case 1:
				//KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
				break;
			case 2:
				//KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
				break;
			default:
				break;
		}

		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE) {
					// todo
					subKeyProcess(i);
					TimerForKeyPress[i] = 200;
				}
			} else {
				TimerForKeyPress[i]--;
				if (TimerForKeyPress[i] == 0) {
					KeyReg3[i] == NORMAL_STATE;
				}
			}
		}
	}
}
