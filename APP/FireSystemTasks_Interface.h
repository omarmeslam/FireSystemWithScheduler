/*
 * FireSystemTasks_Interface.h
 *
 *  Created on: 8 Feb 2024
 *      Author: OMAR
 */

#ifndef APP_FIRESYSTEMTASKS_INTERFACE_H_
#define APP_FIRESYSTEMTASKS_INTERFACE_H_


void vInitEcu(void);
void Task_SensorsReading(void);
void Task_KeyPadPressed(void);
void Task_LCD_DisplayDada(void);
void Task_ActionsON(void);
void Task_CommunicationSend(void);

typedef enum{
	STATE_1,
	STATE_2,
	STATE_3
	}SystemStates_t;

#endif /* APP_FIRESYSTEMTASKS_INTERFACE_H_ */
