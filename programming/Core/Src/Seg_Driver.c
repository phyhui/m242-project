/*
 * 7Seg_Driver.c
 *
 *  Created on: 10.06.2020
 *      Author: famil
 */

#include "Seg_Driver.h"


/* Segment byte maps for numbers 0 to 9 */
const char SEGMENT_MAP[] = {~0xFC,~0x60,~0xDA,~0xF2,~0x66,~0xB6,~0xBE,~0xE0,~0xFE,~0xF6};  // 1 = Segment leuchtet
const char SEGMENT_DP = ~0x01;
/* Byte maps to select digit 1 to 4 */
const char SEGMENT_SELECT[] = {0x10,0x20,0x40,0x80};


/*Configure GPIO pin Output Level */




static int actvalue;  // Aktueller Wert auf der Anzeige
static int actdp;     // Maske f�r den aktuellen Dezimalpunkt
static int actflash;  // noch nicht untertst�zt


void WritePort(int val)
{
	int i;
	static int out;

	out = val;

	for (i=0;i<=7;i++)
	{
	  WRITE_SFTCLK_0;
	  if (out & 0x01)  WRITE_SDI_Pin_1;  // Daten Bitweise ausgeben
	  else             WRITE_SDI_Pin_0;
	  out = out>>1;
	  WRITE_SFTCLK_1;
	}
}


void WriteValue(int digit)
{
   static int disable;
   static int flashcount;
   int val = actvalue;

   int out;
   int out_dp = 0xFF;


  switch (digit)
  {
  case 0:   out = val % 10;               // Stelle 0
            if (actdp & SEG_Driver_DP_1)  out_dp = SEGMENT_DP;
            break;
  case 1:   out = (val / 10) % 10;        // Stelle 1
            if (actdp & SEG_Driver_DP_2)  out_dp = SEGMENT_DP;
            break;
  case 2:   out = (val / 100 % 10);       // Stelle 2
            if (actdp & SEG_Driver_DP_3)  out_dp = SEGMENT_DP;
            break;
  case 3:   out = val / 1000;             // Stelle 3
            if (actdp & SEG_Driver_DP_4)  out_dp = SEGMENT_DP;
            break;
  default:  out = 0;
  }


  WRITE_LCHCLK_0;                          // Daten starten

  // Blinken bearbeiten
  switch(actflash)
  {
  case SEG_Driver_FLASH_OFF:  // blinken ausgeschaltet
  default:                    disable = 0;
	                          break;
  case SEG_Driver_FLASH_FAST: flashcount =flashcount+3;
  case SEG_Driver_FLASH_SLOW: flashcount++;
                              if (!(flashcount%100))     //   100 * 5ms = 500ms => 1s Periodenzeit = 1Hz für langsames blinken
                              {
                            	 if (disable) disable = 0;
                            	 else         disable = 1;
                              }
                              break;
  }

  if (actvalue<= 9999 && actvalue >=0 && !disable)   WritePort(SEGMENT_MAP[out] & out_dp);    // LSB = 7-Segment
  else                                               WritePort(0xFF & out_dp);                // Anzeige Dunkel
  WritePort(SEGMENT_SELECT[digit]);        // MSB = Anzeigen Select

  WRITE_LCHCLK_1;                          // Alle Daten �bernehmen
}



void SEG_Driver_Write(int value, int dp, int flash)
{
 actvalue= value;  // Maximalwert 9999
 actdp   = dp;
 actflash = flash;

}

void SEG_Driver_Task_5ms(void)
{
  static int actdigit;

  actdigit++;
  WriteValue(actdigit % 4);
}

//void SEG_Driver_Init_7(void)
//{
//}


