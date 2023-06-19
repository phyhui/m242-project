/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Taster Treiber

PURPOSE:    Dieser Treiber liest die Taster des Mikrocontrollers aus.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "Taster_Treiber.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------
static bool TASTER_1_STATUS = false;
static bool TASTER_2_STATUS = false;
static bool TASTER_3_STATUS = false;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Reads the state of the given taster and saves it to the static variable
void Taster_Treiber_Init_Task(void *argument)
{
    // Invert the state because the taster is active low (on = 0, off = 1)
    while (true)
    {
        TASTER_1_STATUS = !HAL_GPIO_ReadPin(GPIOA, TASTER_1_Pin);
        TASTER_2_STATUS = !HAL_GPIO_ReadPin(GPIOA, TASTER_2_Pin);
        TASTER_3_STATUS = !HAL_GPIO_ReadPin(TASTER_3_GPIO_Port, TASTER_3_Pin);

        // Wait 50ms to avoid bouncing
        osDelay(50);
    }
}

// Reads the current state of the given taster and returns it
bool Taster_Get(int taster)
{
    switch (taster)
    {
    case TASTER_1:
        return TASTER_1_STATUS;
    case TASTER_2:
        return TASTER_2_STATUS;
    case TASTER_3:
        return TASTER_3_STATUS;
    default:
        return false;
    }
}
