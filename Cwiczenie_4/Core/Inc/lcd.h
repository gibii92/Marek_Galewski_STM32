/*
 * lcd.h
 *
 *  Created on: Jul 15, 2022
 *      Author: szymo
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#define HD44780_CLEAR					 	0x01

#define HD44780_HOME						0x02

#define HD44780_ENTRY_MODE				  	0x04
	#define HD44780_EM_SHIFT_CURSOR		 	0
	#define HD44780_EM_SHIFT_DISPLAY	 	1
	#define HD44780_EM_DECREMENT		   	0
	#define HD44780_EM_INCREMENT		   	2

#define HD44780_DISPLAY_ONOFF			   	0x08
	#define HD44780_DISPLAY_OFF		     	0
	#define HD44780_DISPLAY_ON			   	4
	#define HD44780_CURSOR_OFF			   	0
	#define HD44780_CURSOR_ON			    2
	#define HD44780_CURSOR_NOBLINK	   		0
	#define HD44780_CURSOR_BLINK		   	1

#define HD44780_DISPLAY_CURSOR_SHIFT 		0x10
	#define HD44780_SHIFT_CURSOR		   	0
	#define HD44780_SHIFT_DISPLAY		   	8
	#define HD44780_SHIFT_LEFT			   	0
	#define HD44780_SHIFT_RIGHT		     	4

#define HD44780_FUNCTION_SET			   	0x20
	#define HD44780_FONT5x7				    0
	#define HD44780_FONT5x10			    4
	#define HD44780_ONE_LINE			    0
	#define HD44780_TWO_LINE			    8
	#define HD44780_4_BIT				    0
	#define HD44780_8_BIT				    16

#define HD44780_CGRAM_SET				    0x40

#define HD44780_DDRAM_SET				    0x80

void LCD_Initialize(void);
void LCD_WriteData(char dataToWrite);
void LCD_WriteCommand(char commandToWrite);
void LCD_WriteText(char * text);
void LCD_WriteTextXY(char * text, unsigned char x, unsigned char y);
void LCD_GoTo(unsigned char x, unsigned char y);
void LCD_WriteBinary(unsigned int var, unsigned char bitCount);
void LCD_SetUserChar (char chrNum, unsigned char n, const char *p);

#endif /* INC_LCD_H_ */
