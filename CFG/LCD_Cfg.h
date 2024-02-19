/*
 * LCD_Cfg.h
 *
 * Created: 14/06/2023 15:38:36
 *  Author: OMAR
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define _4_BIT  0
#define _8_BIT  1

/************************** _8_BIT or _4_BIT **********************/
#define LCD_MODE  _4_BIT

/************************** 4 BIT only ***************************/
#define D4  PINA3_PR
#define D5  PINA4_PR
#define D6  PINA5_PR
#define D7  PINA6_PR


#define RS  PINA1_PR

#define E   PINA2_PR

/************************** 8 BIT only ***************************/
#define LCD_PORT  PA

#endif /* LCD_CFG_H_ */
