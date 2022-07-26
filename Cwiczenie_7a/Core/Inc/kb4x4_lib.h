/*
 * kb4x4_lib.h
 *
 *  Created on: Jul 21, 2022
 *      Author: szymo
 */

#ifndef INC_KB4X4_LIB_H_
#define INC_KB4X4_LIB_H_

//linie GPIO obslugi wierszy (Row lines)
#define KB4x4_R1_GPIO_Port GPIOI
#define KB4x4_R1_Pin GPIO_PIN_2
#define KB4x4_R2_GPIO_Port GPIOA
#define KB4x4_R2_Pin GPIO_PIN_15
#define KB4x4_R3_GPIO_Port GPIOA
#define KB4x4_R3_Pin GPIO_PIN_8
#define KB4x4_R4_GPIO_Port GPIOB
#define KB4x4_R4_Pin GPIO_PIN_15

//linie GPIO obslugi kolumn (Column lines)
#define KB4x4_C1_GPIO_Port GPIOB
#define KB4x4_C1_Pin GPIO_PIN_14
#define KB4x4_C2_GPIO_Port GPIOI
#define KB4x4_C2_Pin GPIO_PIN_1
#define KB4x4_C3_GPIO_Port GPIOB
#define KB4x4_C3_Pin GPIO_PIN_9
#define KB4x4_C4_GPIO_Port GPIOB
#define KB4x4_C4_Pin GPIO_PIN_8

//mapowanie klawiszy - kody ASCII
#define KB4x4_R1C1 0x31 //1
#define KB4x4_R1C2 0x32 //2
#define KB4x4_R1C3 0x33 //3
#define KB4x4_R1C4 0x41 //A

#define KB4x4_R2C1 0x34 //4
#define KB4x4_R2C2 0x35 //5
#define KB4x4_R2C3 0x36 //6
#define KB4x4_R2C4 0x42 //B

#define KB4x4_R3C1 0x37 //7
#define KB4x4_R3C2 0x38 //8
#define KB4x4_R3C3 0x39 //9
#define KB4x4_R3C4 0x43 //C

#define KB4x4_R4C1 0x2A //*
#define KB4x4_R4C2 0x30 //0
#define KB4x4_R4C3 0x23 //#
#define KB4x4_R4C4 0x44 //D

void KB4x4_Config();
char KB4x4_ReadKey();
#endif /* INC_KB4X4_LIB_H_ */
