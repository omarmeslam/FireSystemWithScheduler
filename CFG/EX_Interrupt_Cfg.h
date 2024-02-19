

#ifndef EX_INTERRUPT_CFG_H_
#define EX_INTERRUPT_CFG_H_


typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_type;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;

 



#define   EX_INT0_EDGE_MODE   FALLING_EDGE
#define   EX_INT1_EDGE_MODE   RISING_EDGE
#define   EX_INT2_EDGE_MODE   RISING_EDGE





#endif /* EX_INTERRUPT_CFG_H_ */