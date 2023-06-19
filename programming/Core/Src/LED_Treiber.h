/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      LED Treiber

PURPOSE:    Dieser Treiber steuert die LEDs des Mikrocontrollers.

------------------------------------------------------------------------*/

#ifndef _LED_TREIBER
#define _LED_TREIBER

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

#define LED_1 0
#define LED_2 1
#define LED_3 2
#define LED_4 3

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Changes the state of the LED to the opposite of its current state
// Use the constants LED_1 to LED_4 to select the LED
void LED_Toggle(int led);

// Sets the state of the LED to the given state
// state = true: LED is on
// state = false: LED is off
// Use the constants LED_1 to LED_4 to select the LED
void LED_Set(int led, bool state);

#endif
