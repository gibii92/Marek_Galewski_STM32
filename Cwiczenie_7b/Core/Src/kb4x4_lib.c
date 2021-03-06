/*
 * kb4x4_lib.c
 *
 *  Created on: Jul 21, 2022
 *      Author: szymo
 */
#include "kb4x4_lib.h"
#include "stm32f7xx_hal.h"



const char kbKeyMap[4][4] =
{
		{KB4x4_R1C1,KB4x4_R2C1,KB4x4_R3C1,KB4x4_R4C1},
		{KB4x4_R1C2,KB4x4_R2C2,KB4x4_R3C2,KB4x4_R4C2},
		{KB4x4_R1C3,KB4x4_R2C3,KB4x4_R3C3,KB4x4_R4C3},
		{KB4x4_R1C4,KB4x4_R2C4,KB4x4_R3C4,KB4x4_R4C4}
};

 uint16_t kbRows_Pin[4] = {KB4x4_R1_Pin,KB4x4_R2_Pin,KB4x4_R3_Pin,KB4x4_R4_Pin};
 GPIO_TypeDef * kbRows_Port[4] = {KB4x4_R1_GPIO_Port,KB4x4_R2_GPIO_Port,KB4x4_R3_GPIO_Port,KB4x4_R4_GPIO_Port};
 uint16_t kbColumn_Pin[4] = {KB4x4_C1_Pin,KB4x4_C2_Pin,KB4x4_C3_Pin,KB4x4_C4_Pin};
 GPIO_TypeDef * kbColumn_Port[4] = {KB4x4_C1_GPIO_Port,KB4x4_C2_GPIO_Port,KB4x4_C3_GPIO_Port,KB4x4_C4_GPIO_Port};

void KB4x4_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOK_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	  GPIO_InitStruct.Pin = KB4x4_R1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_R1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_R2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_R2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_R3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_R3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_R4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_R4_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_C1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_C1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_C2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_C2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_C3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_C3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = KB4x4_C4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(KB4x4_C4_GPIO_Port, &GPIO_InitStruct);



}
char KB4x4_ReadKey()
{
	unsigned char row, column;
	char pressedKey = 0x00;

	row = 0;
	while(row<4)
	{
		//aktywuj wiersz
		HAL_GPIO_WritePin(kbRows_Port[row], kbRows_Pin[row], GPIO_PIN_SET);
		column = 0;
		while(column<4)
		{
			//sprawdz czy kolumna jest aktywna
			if(HAL_GPIO_ReadPin(kbColumn_Port[column], kbColumn_Pin[column])==GPIO_PIN_SET)
			{
				pressedKey= kbKeyMap[row][column];
			}
			column++;
		}
		//dezaktywuj wiersz
		HAL_GPIO_WritePin(kbRows_Port[row], kbRows_Pin[row], GPIO_PIN_RESET);
		row++;
	}
	//zwroc kod ASCII klawisza
	return pressedKey;
}
