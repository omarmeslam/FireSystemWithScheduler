/*
 * TempFilter_Interface.h
 *
 *  Created on: 8 Feb 2024
 *      Author: OMAR
 */

#ifndef APP_TEMPFILTER_INTERFACE_H_
#define APP_TEMPFILTER_INTERFACE_H_


void Filter_Init(void);
void Filter_Runnable(void);

u16 Filter_GetFilteredTemp(void);
u16 Filter_GetUnFilteredTemp(void);


#endif /* APP_TEMPFILTER_INTERFACE_H_ */
