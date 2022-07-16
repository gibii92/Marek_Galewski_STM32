/*
 * lcd.c
 *
 *  Created on: Jul 15, 2022
 *      Author: szymo
 */
#include "lcd.h"
#include "gpio.h"
GPIO_InitTypeDef GPIO_InitStruct;
//-----------------------------------------------------------------------------
void LCD_WriteNibble(char nibbleToWrite)
{
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (GPIO_PinState)(nibbleToWrite & 0x01));
  HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (GPIO_PinState)(nibbleToWrite & 0x02));
  HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (GPIO_PinState)(nibbleToWrite & 0x04));
  HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (GPIO_PinState)(nibbleToWrite & 0x08));
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
}
//-----------------------------------------------------------------------------
unsigned char LCD_ReadNibble(void)
{
  unsigned char tmp = 0;
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
  tmp |= (HAL_GPIO_ReadPin(LCD_D4_GPIO_Port, LCD_D4_Pin) << 0);
  tmp |= (HAL_GPIO_ReadPin(LCD_D5_GPIO_Port, LCD_D5_Pin) << 1);
  tmp |= (HAL_GPIO_ReadPin(LCD_D6_GPIO_Port, LCD_D6_Pin) << 2);
  tmp |= (HAL_GPIO_ReadPin(LCD_D7_GPIO_Port, LCD_D7_Pin) << 3);
  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
  return tmp;
}
//-----------------------------------------------------------------------------
void LCD_SetDataPinInput(void)
{
	GPIO_InitStruct.Pin =  LCD_D4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin =  LCD_D5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin =  LCD_D6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin =  LCD_D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D7_GPIO_Port, &GPIO_InitStruct);

}
//-----------------------------------------------------------------------------
void LCD_SetDataPinOutput(void)
{
	GPIO_InitStruct.Pin = LCD_D4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_D7_GPIO_Port, &GPIO_InitStruct);

}
//-----------------------------------------------------------------------------
unsigned char LCD_ReadStatus(void)
{
  unsigned char status = 0;

  LCD_SetDataPinInput();

  HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);

  status |= (LCD_ReadNibble() << 4);
  status |= LCD_ReadNibble();

  LCD_SetDataPinOutput();

  return status;
}
//-----------------------------------------------------------------------------
void LCD_WriteData(char dataToWrite)
{
  HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);

  LCD_WriteNibble(dataToWrite >> 4);
  LCD_WriteNibble(dataToWrite & 0x0F);

  while(LCD_ReadStatus() & 0x80);
}
//-----------------------------------------------------------------------------
void LCD_WriteCommand(char commandToWrite)
{
  HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
  LCD_WriteNibble(commandToWrite >> 4);
  LCD_WriteNibble(commandToWrite & 0x0F);

  while(LCD_ReadStatus() & 0x80);
}
//-----------------------------------------------------------------------------
void LCD_WriteText(char * text)
{
  while(*text)
    LCD_WriteData(*text++);
}
void LCD_GoTo(unsigned char x, unsigned char y)
{
  LCD_WriteCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}
//-----------------------------------------------------------------------------
void LCD_WriteTextXY(char * text, unsigned char x, unsigned char y)
{
  LCD_GoTo(x,y);
  while(*text)
    LCD_WriteData(*text++);
}
//-----------------------------------------------------------------------------
void LCD_WriteBinary(unsigned int var, unsigned char bitCount)
{
  signed char i;

  for(i = (bitCount - 1); i >= 0; i--) {
     LCD_WriteData((var & (1 << i))?'1':'0');
  }
}
//-----------------------------------------------------------------------------
void LCD_ShiftLeft(void)
{
  LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_LEFT | HD44780_SHIFT_DISPLAY);
}


//-----------------------------------------------------------------------------
void LCD_ShiftRight(void)
{
  LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_RIGHT | HD44780_SHIFT_DISPLAY);
}
//-----------------------------------------------------------------------------
void LCD_SetControlPinOutput(void)
{
	GPIO_InitStruct.Pin = LCD_RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_RS_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_RW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_RW_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_E_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_E_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);

}
//-----------------------------------------------------------------------------
void LCD_Initialize(void)
{
  volatile unsigned char i = 0;
  volatile unsigned int delayCnt = 0;

  LCD_SetDataPinOutput();
  LCD_SetControlPinOutput();

  for(delayCnt = 0; delayCnt < 300000; delayCnt++);

  for(i = 0; i < 3; i++) {
    LCD_WriteNibble(0x03);
    for(delayCnt = 0; delayCnt < 30000; delayCnt++);
  }

  LCD_WriteNibble(0x02);

  for(delayCnt = 0; delayCnt < 6000; delayCnt++);

  LCD_WriteCommand(HD44780_FUNCTION_SET |
                   HD44780_FONT5x7 |
                   HD44780_TWO_LINE |
                   HD44780_4_BIT);

  LCD_WriteCommand(HD44780_DISPLAY_ONOFF |
                   HD44780_DISPLAY_OFF);

  LCD_WriteCommand(HD44780_CLEAR);

  LCD_WriteCommand(HD44780_ENTRY_MODE |
                   HD44780_EM_SHIFT_CURSOR |
                   HD44780_EM_INCREMENT);

  LCD_WriteCommand(HD44780_DISPLAY_ONOFF |
                   HD44780_DISPLAY_ON |
                   HD44780_CURSOR_OFF |
                   HD44780_CURSOR_NOBLINK);
}
//-----------------------------------------------------------------------------
void LCD_SetUserChar (char chrNum, unsigned char n, const char *p)
{         //chrNum  - character number (code) to be registered (0..7)
          //n       - number of characters to register
          //*p      - pointer to the character pattern (8 * n bytes)
	LCD_WriteCommand(HD44780_CGRAM_SET | chrNum * 8);
	n *= 8;
	do
		LCD_WriteData(*p++);
	while (--n);
}

