/*
 * DIO_Interface.h
 *
 * Created: 12/06/2023 00:13:43
 *  Author: OMAR
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum{
	PINA0_PR=0,
	PINA1_PR=1,
	PINA2_PR,
	PINA3_PR,
	PINA4_PR,
	PINA5_PR,
	PINA6_PR,
	PINA7_PR,
	PINB0_PR,
	PINB1_PR,
	PINB2_PR,
	PINB3_PR,
	PINB4_PR,
	PINB5_PR,
	PINB6_PR,
	PINB7_PR,
	PINC0_PR,
	PINC1_PR,
	PINC2_PR,
	PINC3_PR,
	PINC4_PR,
	PINC5_PR,
	PINC6_PR,
	PINC7_PR,
	PIND0_PR,
	PIND1_PR,
	PIND2_PR,
	PIND3_PR,
	PIND4_PR,
	PIND5_PR,
	PIND6_PR,
	PIND7_PR,
	TOTAL_PINS
}DIO_Pin_type;



typedef enum{
	OUTPUT,
	INFREE,
	INPULL
}DIO_PinStatus_type;

typedef enum{
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_type;

typedef enum{
	LOW,
	HIGH
	}DIO_PinVoltage_type;

void DIO_Init(void);
void DIO_WritePin(DIO_Pin_type pin, DIO_PinVoltage_type volt);
DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin);

void DIO_TogglePin(DIO_Pin_type pin);
void DIO_WritePort(DIO_Port_type port, u8 data);
u8 DIO_ReadPort(DIO_Port_type port);

#endif /* DIO_INTERFACE_H_ */