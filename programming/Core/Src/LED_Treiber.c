/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      LED Treiber

PURPOSE:    Dieser Treiber steuert die LEDs des Mikrocontrollers.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "LED_Treiber.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Changes the state of the LED to the opposite of its current state
void LED_Toggle(int led)
{
    switch (led)
    {
    case LED_1:
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        break;
    case LED_2:
        HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
        break;
    case LED_3:
        HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
        break;
    case LED_4:
        HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
        break;
    default:
        break;
    }
}

// Sets the state of the LED to the given state
void LED_Set(int led, bool state)
{
    // Invert the state because the LEDs are active low (on = 0, off = 1)
    switch (led)
    {
    case LED_1:
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, !state);
        break;
    case LED_2:
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, !state);
        break;
    case LED_3:
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, !state);
        break;
    case LED_4:
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, !state);
        break;
    default:
        break;
    }
}
