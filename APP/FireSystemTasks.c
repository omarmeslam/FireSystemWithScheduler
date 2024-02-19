
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "MOTOR_Interface.h"
#include "Sensors_Interface.h"
#include "FireSysTasks_Cfg.h"
#include "FireSystemTasks_Interface.h"
#include "FireSystemTasks_Private.h"
#include "TempFilter_Interface.h"
#include "KeyPad_Interface.h"
#include "NVM_Services.h"
#include "BCM_Services.h"

#define  F_CPU  8000000UL
#include <util/delay.h>


static u16 temp,smoke;
static u8 StopFlag=0,FineFlag,HeatFlag,FireFlag,messageFlag,PassChangeFlag,PassEditedFlag,SystemResetFlag;
static c8 SystemPassword[10]="4321";
static u8 SysPassIndex,SysPassDisplayedIndex,GetPassIndex,GetPassFlag,PassTryFlagDisplayed,DisplayFlag,PassTryFlag;
static c8 GetPassword[10];
static SystemStates_t state=STATE_1;
Error_t status=OK;


void vInitEcu(void)
{


	for (u8 i=0;EEPROM_Read(i)!=0;i++)
	{
		SystemPassword[i]=EEPROM_Read(i);
	}

	MOTOR_Stop(M2);
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FIRE_LED,LOW);
	LCD_GoTo(0,6);
	//LCD_WriteString("Fine");


	Filter_Init();
}


void Task_SensorsReading(void)
{

	Filter_Runnable();

	temp=Filter_GetFilteredTemp();
	if (temp>500 && (state!=STATE_3))
	{
		/*Heat State*/
		state = STATE_2;
		FineFlag=0;
		HeatFlag=1;
		FireFlag=0;

	}
	else if (temp<450 && (state!=STATE_3))
	{
		/*Fine State*/
		state = STATE_1;
		FineFlag=1;
		HeatFlag=0;
		FireFlag=0;

	}
	else
	{
		/* still last state */
	}


	smoke=POT_Smoke_Read();
	if (temp>500 && smoke>50)
	{
		/*Fire State*/
		state = STATE_3;
		FineFlag=0;
		HeatFlag=0;
		FireFlag=1;
	}
	else
	{
		/* still last state */
	}


}



void Task_KeyPadPressed(void)
{
	u8 k=NO_KEY;

	k=KEYPAD_GetKey();

	if (k!=NO_KEY && (state==STATE_3 || StopFlag==1))
	{
		if (k=='1' && StopFlag==0)
		{
			StopFlag = 1;
			DisplayFlag=1;
		}
		else if (k>='0' && k<='9' && StopFlag==1)
		{
			GetPassword[GetPassIndex]=k;
			GetPassFlag=1;
		}
		else if (k=='=' && StopFlag==1)
		{
			status = StringCompare(GetPassword,SystemPassword);
			if (status==OK)
			{
				SystemResetFlag=1;
			}
			else
			{
				PassTryFlagDisplayed=1;
				PassTryFlag=1;
				DisplayFlag=1;
			}
			StopFlag = 0;
			GetPassFlag=0;
			GetPassIndex=0;

		}
	}



	if (k=='2'&& PassChangeFlag==0 && (state==STATE_1 || state==STATE_2))
	{
		PassChangeFlag=1;
		DisplayFlag=1;
	}

	else if (PassChangeFlag==1)
	{
		if (k >= '0' && k <= '9')
		{
			SystemPassword[SysPassIndex] = k;
			EEPROM_Write(SysPassIndex, k);
			PassEditedFlag = 1;
			SysPassIndex++;
		}
		else if (k == '=')
		{
			SystemPassword[SysPassIndex] = 0;
			EEPROM_Write(SysPassIndex, 0);
			LCD_Clear();
			SysPassIndex = 0;
			SysPassDisplayedIndex = 0;
			PassChangeFlag = 0;
			PassEditedFlag = 0;
		}
	}

}




void Task_LCD_DisplayDada(void)
{
	if(!PassChangeFlag && !StopFlag && !PassTryFlag)
	{
		LCD_WriteState(state);
		LCD_WriteTemp(temp);
		LCD_WriteSmoke(smoke);
	}


	if(state != STATE_3)
	{
		if(!PassChangeFlag)
		{
			LCD_GoTo(1, 5);
			LCD_WriteString("Edit Pass:2");
		}


		if(PassChangeFlag && DisplayFlag)
		{
			LCD_Clear();
			LCD_GoTo(0, 0);
			LCD_WriteString("Enter New Password");
			LCD_GoTo(1, 0);
			DisplayFlag=0;
		}

		else if(PassEditedFlag)
		{
			LCD_WriteChar(SystemPassword[SysPassDisplayedIndex]);
			SysPassDisplayedIndex++;
			PassEditedFlag=0;
		}


	}
	else
	{
		if(!StopFlag && !PassTryFlag)
		{
			LCD_GoTo(1,5);
			LCD_WriteString("   Stop:1   ");
		}

		if(StopFlag && DisplayFlag)
		{
			LCD_Clear();
			LCD_GoTo(0, 0);
			LCD_WriteString("Enter Password");
			LCD_GoTo(1, 0);
			DisplayFlag=0;
		}
		else if (GetPassFlag)
		{
			LCD_WriteChar(GetPassword[GetPassIndex]);
			GetPassIndex++;
			GetPassFlag=0;
		}

		else if (PassTryFlagDisplayed)
		{
			LCD_Clear();
			LCD_GoTo(0, 0);
			LCD_WriteString("Wrong Password");
			LCD_GoTo(1, 0);
			LCD_WriteString("1 to try again");
			PassTryFlagDisplayed = 0;
		}
	}
}


void Task_CommunicationSend(void)
{
	if(messageFlag)
	{
		UART_SendStringAsynch("message: system is fire");
		UART_SendStringAsynch(", please fix the problem");
		messageFlag=0;
	}
	BCM_Runnable();
}



void Task_ActionsON(void)
{
	if(FineFlag)
	{
		DIO_WritePin(HEAT_LED,LOW); //Fine State
	}
	else if(HeatFlag)
	{
		DIO_WritePin(HEAT_LED,HIGH); //Heat State
	}
	else if(FireFlag)
	{
		DIO_WritePin(FIRE_LED,HIGH); //Fire State
		DIO_WritePin(BUZZER,HIGH);
		MOTOR_CW(M2);
		UART_SendStringAsynch("message: system is fire");
		UART_SendStringAsynch(", please fix the problem");
	}

	if(SystemResetFlag)
	{
		SystemReset();
		SystemResetFlag=0;
	}

}


u8 GetStatusOfCommTask(void)
{
	return FireFlag;
}


/********************************Private Functions******************************/

static void LCD_WriteState(SystemStates_t state)
{
	LCD_GoTo(0,6);
	if (state==STATE_1)
	{
		LCD_WriteString("Fine");
	}
	else if (state==STATE_2)
	{
		LCD_WriteString("Heat");
	}
	else if (state==STATE_3)
	{
		LCD_WriteString("Fire");
	}
}


static void LCD_WriteTemp(u16 temp)
{
	LCD_GoTo(1,0);
	LCD_WriteNumber(temp/10);
	LCD_WriteChar('c');
	LCD_WriteString("  ");
}


static void LCD_WriteSmoke(u16 smoke)
{
	LCD_GoTo(0,0);
	LCD_WriteNumber(smoke);
	LCD_WriteString("  ");
}





static Error_t StringCompare(c8* str1, c8* str2)
{
	Error_t s=OK;
	u8 i;

	for (i=0; str1[i]||str2[i]; i++)
	{
		if (str1[i]!=str2[i])
		{
			s = NOK;
		}
	}

	return s;
}


static void SystemReset(void)
{
	LCD_Clear();
	DIO_WritePin(HEAT_LED,LOW);
	DIO_WritePin(FIRE_LED,LOW);
	DIO_WritePin(BUZZER,LOW);
	MOTOR_Stop(M2);
	PassTryFlag = 0;
	state = STATE_1;
}
