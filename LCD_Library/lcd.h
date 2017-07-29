/*
 * lcd.h
 *
 *  Created on: Jul 28, 2017
 *      Author: Tejas Laptop
 */

#ifndef LCD_H_
#define LCD_H_

#define EN_VAL	0x02 															/*	According to bit position in lcd.*/
#define RS_VAL	0x01 															/*	According to bit position in lcd.*/

#define UPPER_D7_POS	0X80													/*	Position value of the pin*/
#define UPPER_D6_POS	0X40													/*	Position value of the pin*/
#define UPPER_D5_POS	0X20													/*	Position value of the pin*/
#define UPPER_D4_POS	0X10													/*	Position value of the pin*/
#define LOWER_D7_POS	0X08													/*	Position value of the pin*/
#define LOWER_D6_POS	0X04													/*	Position value of the pin*/
#define LOWER_D5_POS	0X02													/*	Position value of the pin*/
#define LOWER_D4_POS	0X01													/*	Position value of the pin*/

typedef struct
{
	int Enable_Pin;
	int RS_Pin;
	int D4_Pin;
	int D5_Pin;
	int D6_Pin;
	int D7_Pin;

} LCD_Gpio;

int Lcd_Init(LCD_Gpio *);
int Lcd_SendCommand(LCD_Gpio *,unsigned char);									/*	LCD only accepts char data*/
int Lcd_SendData(LCD_Gpio *,unsigned char);
void Lcd_String(LCD_Gpio *,unsigned char*);
void Lcd_Scroll(LCD_Gpio *,unsigned char*);
void Lcd_CmdMode(LCD_Gpio *);
void Lcd_DataMode(LCD_Gpio *);

#endif /* LCD_H_ */
