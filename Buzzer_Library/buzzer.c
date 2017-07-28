/*
 * buzzer.c
 *
 *  Created on: Jul 27, 2017
 *      Author: Tejas Laptop
 */

#include <gpio.h>
#include "buzzer.h"

int Buzzer_Init(int Pin)
{
	if(GPIOExport(Pin) == 0)													/*	Enable GPIO pin for use*/
	{
		sleep(1);
		if(GPIODirection(Pin,OUT))												/*	Set direction for GPIO*/
			goto ERROR_INIT;
	}
	else
		goto ERROR_INIT;

	return 0;

	ERROR_INIT:
	printf("Failed to open the %d GPIO for buzzer\n",Pin);
	return -1;
}



int Buzzer_On(int Pin)
{
	if(GPIOWrite(Pin, 1))														/*	Write GPIO value*/
	{
		printf("Error writing to GPIO pin %d\n",Pin);
		return -1;
	}
	return 0;
}

int Buzzer_Off(int Pin)
{
	if(GPIOWrite(Pin, 0))														/*	Write GPIO value*/
	{
		printf("Error writing to GPIO pin %d\n",Pin);
		return -1;
	}
	return 0;
}

int Buzzer_Toggle(int Pin, int Delay)
{
	if(GPIOWrite(Pin,!GPIORead(Pin)))														/*	Write GPIO value*/
	{
		printf("Error writing to GPIO pin %d\n",Pin);
		return -1;
	}

	usleep(Delay * 10);

	if(GPIOWrite(Pin,!GPIORead(Pin)))														/*	Write GPIO value*/
	{
		printf("Error writing to GPIO pin %d\n",Pin);
		return -1;
	}

	return 0;
}
