/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Taster Treiber

PURPOSE:    Dieser Treiber liest die Taster des Mikrocontrollers aus.

------------------------------------------------------------------------*/

#ifndef _Taster_Treiber
#define _Taster_Treiber

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

#define TASTER_1 0
#define TASTER_2 1
#define TASTER_3 2

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Reads the state of the given taster and saves it to the static variable
// This is a task that should be called by the scheduler
void Taster_Treiber_Init_Task(void *argument);

// Reads the current state of the given taster and returns it
// Use the constants TASTER_1 to TASTER_3 to select the taster
bool Taster_Get(int taster);

#endif
