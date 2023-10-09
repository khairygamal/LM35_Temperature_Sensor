


#ifndef _APPLICATION_H
#define	_APPLICATION_H

/*** SEction : Includes ***/
#include "ECU_Layer/ecu_layer.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "../TESt.X/MCAL_Layer/ADC/hal_adc.h"
//#include "ECU_Layer/chr_LCD/ecu_chr_lcd.h"
#include "MCAL_Layer/ADC/hal_adc.h"
//#include "MCAL_Layer/Timer1/hal_timer1.h"
//#include "MCAL_Layer/Timer2/hal_timer2.h"
//#include "MCAL_Layer/Timer3/hal_timer3.h"
#include <htc.h>
#include <xc.h>
/*** SEction : Macros Decleration ***/
#define _XTAL_FREQ 8000000UL

/*** SEction : Macros Function ***/

/*** SEction : Data Types Decleration ***/
//extern keypad_t keypad_1;
//extern chr_lcd_8bit_t lcd_1;
/*** SEction : Fuction Decleration ***/
void application_intialize(void);


#endif	/* _APPLICATION_H */

