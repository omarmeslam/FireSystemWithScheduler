
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "EX_Interrupt_Interface.h"
#include "UART_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "TIMERS_Interface.h"
#include "NVM_Services.h"
#include "BCM_Services.h"
#include "FireSystemTasks_Interface.h"
#include "OS.h"

#define  F_CPU  8000000UL
#include <util/delay.h>



// ISR Callback
void vMillisIncrement(void)
{
	/* called every 2000 us
	 * 50ms = 50000 us
	 * count to 25 times to reach 50ms*/

	static u8 u8_50msCounter;


	u8_50msCounter++;


	if(u8_50msCounter >= 25)
	{
		/*call task handler*/
		u8_50msCounter = 0;
		OS_Task_Handler();
		TCNT0=6;
	}
}






void InitScheduler(void)
{
	TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_64);
	TIMER0_OV_InterruptEnable();
	TIMER0_OV_SetCallBack(vMillisIncrement);
	TCNT0=6;

	OS_TaskCreate(Task_KeyPadPressed,1 , BLOCKED);
	OS_TaskCreate(Task_CommunicationSend,2,SUSPENDED);
	OS_TaskCreate(Task_LCD_DisplayDada,2 , BLOCKED);
	OS_TaskCreate(Task_SensorsReading,20 , BLOCKED);
	OS_TaskCreate(Task_ActionsON,20 , BLOCKED);

}



int main(void)
{
	// Sw initilaization
	DIO_Init();
	LCD_Init();
	ADC_Init();
	EXI_Init();
	KEYPAD_Init();
	UART_Init();
	BCM_Init();
	GLOBAL_ENABLE();

	vInitEcu();

	// Start the Scheduler
	InitScheduler();



	while(1)
	{
		// Execute the scheduler
		OS_TaskExecution();
	}
}
