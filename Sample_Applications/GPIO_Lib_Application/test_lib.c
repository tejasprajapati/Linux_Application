/*
 * test_lib.c
 *
 *  Created on: Jul 26, 2017
 *      Author: Tejas Laptop
 */

#include <stdio.h>
#include <gpio.h>

int main()
{
	int i;
	GPIOExport(4);																/*	Enable GPIO pin for use*/
	sleep(1);
	GPIODirection(4,1);															/*	Set direction for GPIO*/

	for(i = 0; i < 10; i++)
		{
			printf("Writing gpio\n");
			GPIOWrite(4, i % 2);											/*	Write GPIO value*/
			usleep(500 * 1000);
		}

	GPIOUnexport(4);															/*	Disable GPIO pin after use*/
	return 0;
}
