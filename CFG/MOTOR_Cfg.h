/*
 * MOTOR_Cfg.h
 *
 * Created: 12/06/2023 13:39:44
 *  Author: OMAR
 */ 


#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/*********************PIN CONFIG *************************/

#define  M1_IN1   PINC0_PR
#define  M1_IN2   PINC1_PR

#define  M2_IN1   PINC2_PR
#define  M2_IN2   PINC3_PR


#define  M3_IN1   PINC4_PR
#define  M3_IN2   PINC5_PR


#define  M4_IN1   PINC6_PR
#define  M4_IN2   PINC7_PR

DIO_Pin_type MotorPinsArr[4][2]={{M1_IN1,M1_IN2},
					   			 {M2_IN1,M2_IN2},
								 {M3_IN1,M3_IN2},
								 {M4_IN1,M4_IN2}};

#endif /* MOTOR_CFG_H_ */
