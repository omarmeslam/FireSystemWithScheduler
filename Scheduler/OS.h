



#ifndef OS_H_
#define OS_H_

#include "StdTypes.h"

typedef void (*fncPtr)(void);           /**< Function pointer for registering tasks. */

#define   MAX_NUM_OF_TASKS            ((u8)5)
#define   HYPER_PERIOD                ((u16)20)

typedef enum
{
	SUSPENDED,
	BLOCKED,
	READY
} OS_state;


/*Task Control Block*/
typedef struct
{
	fncPtr       function;
	OS_state     task_state;
	u16          Task_tick_counter;
	u16          task_Periodicity;
	/* Priority insured by creation task order*/
} OS_struct;


typedef enum
{
	OS_OK,
	OS_NOK_HYPER_PERIOD_VIOLATION,
	OS_NOK_TASK_COUNT_VIOLATION,
	OS_NOK_NULL_PTR,
	OS_NOK_INIT
} OS_feedback;


OS_feedback OS_TaskCreate(fncPtr task, u16 periodicity, OS_state default_state);

void OS_Task_Handler(void);

void OS_TaskExecution(void);


#endif /* OS_H_ */
