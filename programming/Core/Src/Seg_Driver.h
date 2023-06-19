/*
 * 7Seg_Driver.h
 *
 *  Created on: 10.06.2020
 *      Author: famil
 */

#ifndef SRC_SEG_DRIVER_H_
#define SRC_SEG_DRIVER_H_

#include "main.h"
#include "cmsis_os.h"

// Ausgabe-Funktionen der einzelen Pins f�r das Board Multifunktion Shield definieren

// PA9     OUT_7SEG_SDI_Pin
// PA8     OUT_7SEG_SFTCLK_Pin
// PB5     OUT_7SEGLCHCLK_Pin

#define WRITE_SFTCLK_0  HAL_GPIO_WritePin(GPIOA, OUT_7SEG_SFTCLK_Pin, 0)
#define WRITE_SFTCLK_1  HAL_GPIO_WritePin(GPIOA, OUT_7SEG_SFTCLK_Pin, 1)
#define WRITE_LCHCLK_0  HAL_GPIO_WritePin(GPIOB, OUT_7SEGLCHCLK_Pin,  0)
#define WRITE_LCHCLK_1  HAL_GPIO_WritePin(GPIOB, OUT_7SEGLCHCLK_Pin,  1)
#define WRITE_SDI_Pin_0 HAL_GPIO_WritePin(GPIOA, OUT_7SEG_SDI_Pin,    0)
#define WRITE_SDI_Pin_1 HAL_GPIO_WritePin(GPIOA, OUT_7SEG_SDI_Pin,    1)


#define SEG_Driver_DP_OFF 0       // kein DP
#define SEG_Driver_DP_1   0x1     // Stelle 1 rechts
#define SEG_Driver_DP_2   0x2     // Stelle 2
#define SEG_Driver_DP_3   0x4     // Stelle 3
#define SEG_Driver_DP_4   0x8     // Stelle 4 links

#define SEG_Driver_FLASH_OFF  0
#define SEG_Driver_FLASH_SLOW 1
#define SEG_Driver_FLASH_FAST 2




void SEG_Driver_Write(int value, int dp, int flash);

// Anzeige-Wert schreiben  (negative Werte werden noch nicht unterst�tzt)
// Die Anzeige wird gel�scht, sobald ein Wert gr�sser 9999 �bergeben wird

//  int value   Wert von 0....9999  >9999 Anzeige = OFF
//  int dp		SEG_Driver_DP_OFF  ... SEG_Driver_DP_4              SEG_Driver_DP_1 | SEG_Driver_DP_2   es k�nnen mehrere angew�hlt werden
//  int flash   SEG_Driver_FLASH_OFF  SEG_Driver_FLASH_FAST   SEG_DRIVER_FLAH_SLOW


void SEG_Driver_Task_5ms(void);
// Dieser Task muss alle 5ms aufgerufen werden


#endif /* SRC_SEG_DRIVER_H_ */
