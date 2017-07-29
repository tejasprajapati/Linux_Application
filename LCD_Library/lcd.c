/*
 * lcd.c
 *
 *  Created on: Jul 28, 2017
 *      Author: Tejas Laptop
 */

#include <gpio.h>
#include "lcd.h"

void Lcd_CmdMode(LCD_Gpio *Gpio_Pins)
{
	GPIOWrite(Gpio_Pins->RS_Pin, 0); 											/*	Set for commands*/
}

void Lcd_DataMode(LCD_Gpio *Gpio_Pins)
{
	GPIOWrite(Gpio_Pins->RS_Pin, 1); 											/*	Set for Data*/
}

void PulseEnable(LCD_Gpio *Gpio_Pins)
{
	GPIOWrite(Gpio_Pins->Enable_Pin, 1);
	usleep(1000); 																/*	At least 1ms pulse - enable pulse must be > 450ns*/
	GPIOWrite(Gpio_Pins->Enable_Pin, 0);
}

int Lcd_SendCommand(LCD_Gpio *Gpio_Pins, unsigned char Lcd_Command)
{
	Lcd_CmdMode(Gpio_Pins);

	GPIOWrite(Gpio_Pins->D4_Pin, (Lcd_Command & UPPER_D4_POS));
	GPIOWrite(Gpio_Pins->D5_Pin, (Lcd_Command & UPPER_D5_POS));
	GPIOWrite(Gpio_Pins->D6_Pin, (Lcd_Command & UPPER_D6_POS));
	GPIOWrite(Gpio_Pins->D7_Pin, (Lcd_Command & UPPER_D7_POS));

	PulseEnable(Gpio_Pins);

	GPIOWrite(Gpio_Pins->D4_Pin, (Lcd_Command & LOWER_D4_POS));
	GPIOWrite(Gpio_Pins->D5_Pin, (Lcd_Command & LOWER_D5_POS));
	GPIOWrite(Gpio_Pins->D6_Pin, (Lcd_Command & LOWER_D6_POS));
	GPIOWrite(Gpio_Pins->D7_Pin, (Lcd_Command & LOWER_D7_POS));

	PulseEnable(Gpio_Pins);

	usleep(1000);
	return 0;

}

int Lcd_SendData(LCD_Gpio *Gpio_Pins, unsigned char Lcd_Data)
{
	Lcd_DataMode(Gpio_Pins);

	GPIOWrite(Gpio_Pins->D4_Pin, (Lcd_Data & UPPER_D4_POS));
	GPIOWrite(Gpio_Pins->D5_Pin, (Lcd_Data & UPPER_D5_POS));
	GPIOWrite(Gpio_Pins->D6_Pin, (Lcd_Data & UPPER_D6_POS));
	GPIOWrite(Gpio_Pins->D7_Pin, (Lcd_Data & UPPER_D7_POS));

	PulseEnable(Gpio_Pins);

	GPIOWrite(Gpio_Pins->D4_Pin, (Lcd_Data & LOWER_D4_POS));
	GPIOWrite(Gpio_Pins->D5_Pin, (Lcd_Data & LOWER_D5_POS));
	GPIOWrite(Gpio_Pins->D6_Pin, (Lcd_Data & LOWER_D6_POS));
	GPIOWrite(Gpio_Pins->D7_Pin, (Lcd_Data & LOWER_D7_POS));

	PulseEnable(Gpio_Pins);

	usleep(1000);
	return 0;
}

int Lcd_Init(LCD_Gpio *Gpio_Pins)
{
	GPIOExport(Gpio_Pins->Enable_Pin);
	GPIOExport(Gpio_Pins->RS_Pin);
	GPIOExport(Gpio_Pins->D4_Pin);
	GPIOExport(Gpio_Pins->D5_Pin);
	GPIOExport(Gpio_Pins->D6_Pin);
	GPIOExport(Gpio_Pins->D7_Pin);

	GPIODirection(Gpio_Pins->Enable_Pin, OUT);
	GPIODirection(Gpio_Pins->RS_Pin, OUT);
	GPIODirection(Gpio_Pins->D4_Pin, OUT);
	GPIODirection(Gpio_Pins->D5_Pin, OUT);
	GPIODirection(Gpio_Pins->D6_Pin, OUT);
	GPIODirection(Gpio_Pins->D7_Pin, OUT);

	Lcd_SendCommand(Gpio_Pins,0x38);
	Lcd_SendCommand(Gpio_Pins,0x83);
	Lcd_SendCommand(Gpio_Pins,0x03);
	Lcd_SendCommand(Gpio_Pins,0x82);
	Lcd_SendCommand(Gpio_Pins,0x02);
	Lcd_SendCommand(Gpio_Pins,0x28);
	Lcd_SendCommand(Gpio_Pins,0x28);
	Lcd_SendCommand(Gpio_Pins,0x10);
	Lcd_SendCommand(Gpio_Pins,0x01);
	Lcd_SendCommand(Gpio_Pins,0x0F);
	Lcd_SendCommand(Gpio_Pins,0x0C);
	Lcd_SendCommand(Gpio_Pins,0x06);
	Lcd_SendCommand(Gpio_Pins,0x01);
	Lcd_SendCommand(Gpio_Pins,0x80);

	return 0;
}

void Lcd_String(LCD_Gpio *Gpio_Pins,unsigned char *str)
{
	while(*str)
	{
		Lcd_SendData(Gpio_Pins,*str++);
	}
}

void Lcd_Scroll(LCD_Gpio *Gpio_Pins, unsigned char *str)
{
	int i;
	int LOC = 0x80;
	for(i=0;str[i]!='\0';i++)
	{
		LOC++;
		Lcd_SendCommand(Gpio_Pins,0x80 | i);
		Lcd_SendData(Gpio_Pins,str[i]);
		Lcd_SendCommand(Gpio_Pins,0x05);
		if(LOC >= 0x8F)															/*	This is the logic that we move text to left side after we reached at*/
			Lcd_SendCommand(Gpio_Pins,0x1C);									/*	Location 0x8F which is last address on LCD in first line*/
	}
}
