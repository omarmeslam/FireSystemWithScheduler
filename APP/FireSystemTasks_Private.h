/*
 * FireSystemTasks_Private.h
 *
 *  Created on: 8 Feb 2024
 *      Author: OMAR
 */

#ifndef APP_FIRESYSTEMTASKS_PRIVATE_H_
#define APP_FIRESYSTEMTASKS_PRIVATE_H_


static void LCD_WriteState(SystemStates_t state);
static void LCD_WriteTemp(u16 temp);
static void LCD_WriteSmoke(u16 smoke);


static Error_t StringCompare(c8* str1, c8* str2);

static void SystemReset(void);


#endif /* APP_FIRESYSTEMTASKS_PRIVATE_H_ */
