
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "WDT_Interface.h"



void WDT_Set(TimeOut_type time)
{
	u8 wdt_value=0x08; //WDE WDTOE CLEARED 0b00001000
	WDTCR |= (1<<WDE) | (1<<WDTOE);
	WDTCR = wdt_value;
}

void WDT_Stop(void)
{
	WDTCR = (1<<WDE) | (1<<WDTOE);
	WDTCR = 0;
}