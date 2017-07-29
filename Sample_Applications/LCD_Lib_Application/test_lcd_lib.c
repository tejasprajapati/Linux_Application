/*
 * test_lcd_lib.c
 *
 *  Created on: Jul 29, 2017
 *      Author: Tejas Laptop
 */

#include <lcd.h>
#include <gpio.h>

static LCD_Gpio Gpio_Pins;

int main()
{
	Gpio_Pins.RS_Pin = 16;
	Gpio_Pins.Enable_Pin = 17;
	Gpio_Pins.D4_Pin = 18;
	Gpio_Pins.D5_Pin = 19;
	Gpio_Pins.D6_Pin = 20;
	Gpio_Pins.D7_Pin = 21;

	Lcd_Init(&Gpio_Pins);

	Lcd_String(&Gpio_Pins,"Tejas Prajapati");
	while(1)
	{
		Lcd_Scroll(&Gpio_Pins, "Hello World Tejas Here");
		usleep(200000);
	}

	return 0;
}
