/*
 * EX_Interrupt_Interface.h
 *
 * Created: 15/07/2023 13:54:28
 *  Author: OMAR
 */ 


#ifndef EX_INTERRUPT_INTERFACE_H_
#define EX_INTERRUPT_INTERFACE_H_

#include "EX_Interrupt_Cfg.h"

void EXI_Init(void);

#define   GLOBAL_ENABLE    sei

void EXI_Enable(ExInterruptSource_type Interrupt);
void EXI_Disable(ExInterruptSource_type Interrupt);
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge);
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void));


#endif /* EX_INTERRUPT_INTERFACE_H_ */