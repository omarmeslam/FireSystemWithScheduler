/*
 * Tasks.c
 *
 *  Created on: May 7, 2021
 *      Author: Zack
 */


#include "Tasks.h"
#include <util/delay.h>
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "TIMERS_Interface.h"






void Task_2S_Blink(void)
{
	DIO_TogglePin(PINB1_PR);
}


void Task_1S_LcdUpdate(void)
{
	static u16 u16Seconds = 1;
	LCD_GoTo(0,10);
	LCD_WriteNumber(u16Seconds);
	u16Seconds++;

}

void Task_3S_Blink(void)
{
	DIO_TogglePin(PINB2_PR);
}
