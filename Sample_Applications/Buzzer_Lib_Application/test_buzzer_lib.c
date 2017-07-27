/*
 * test_lib.c
 *
 *  Created on: Jul 26, 2017
 *      Author: Tejas Laptop
 */

#include <buzzer.h>

int main()
{
	Buzzer_Init(4);

	Buzzer_On(4);

	Buzzer_Off(4);

	Buzzer_Toggle(4,1000);

	return 0;
}
