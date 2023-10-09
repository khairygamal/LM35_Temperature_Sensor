/* 
 * File:   application.c
 * Created on September 4, 2023, 2:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "application.h"
#include "../TESt.X/MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer3/hal_timer3.h"
#include "ECU_Layer/Dc_Motor/Dc_Motor.h"
#include "../TESt.X/ECU_Layer/chr_LCD/ecu_chr_lcd.h"


dc_motor_t dc_motor_1 = {
    .dc_motor[0].port = PORTD_INDEX,
    .dc_motor[0].pin = PIN2,
    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTD_INDEX,
    .dc_motor[1].pin =PIN3,
    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t dc_motor_2 = {
    .dc_motor[0].port = PORTD_INDEX,
    .dc_motor[0].pin = PIN4,
    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTD_INDEX,
    .dc_motor[1].pin = PIN5,
    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
};

chr_lcd_8bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[4].port = PORTC_INDEX,
    .lcd_data[4].pin = PIN6,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOW, 
    .lcd_data[5].port = PORTC_INDEX,
    .lcd_data[5].pin = PIN7,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOW,
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = PIN0,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOW,
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = PIN1,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOW
};

adc_confg_t adc_1 = {
    .ADC_InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .channel_Select= ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLE
};

uint16 lm35_res_1, lm35_res_2, lm35_res_1_Celsius_mv = 0, lm35_res_2_Celsius_mv = 0;
uint8 lm35_res_1_txt[7], lm35_res_2_txt[7];

int main() {
    std_ReturnType ret = E_NOT_OK;
    
    ret = lcd_8bit_intialize(&lcd_1);
    ret = ADC_Init(&adc_1);
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
    
    ret = lcd_8bit_send_string_pos(&lcd_1, 1, 1, "khairi gamal");
    __delay_ms(500);
    ret = lcd_8bit_send_command(&lcd_1,_LCD_CLEAR);
    
    ret = lcd_8bit_send_string_pos(&lcd_1, 1, 3, "LM35 Test");
    
    ret = lcd_8bit_send_string_pos(&lcd_1, 2, 1, "Temp1: ");
    ret = lcd_8bit_send_string_pos(&lcd_1, 3, 1, "Temp2: ");
     
    while (1)
    {
        ret = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN0, &lm35_res_1);
        ret = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN1, &lm35_res_2);
        
        lm35_res_1_Celsius_mv = lm35_res_1 * 4.88f; /* 5000(mv) / 1024(10-Bit) => 4.88 */
        lm35_res_2_Celsius_mv = lm35_res_2 * 4.88f; /* 5000(mv) / 1024(10-Bit) => 4.88 */
        
        lm35_res_1_Celsius_mv /= 10; /* The sensitivity of LM35 is 10 mV/degree Celsius */
        lm35_res_2_Celsius_mv /= 10; /* The sensitivity of LM35 is 10 mV/degree Celsius */
        
        ret = Convert_short_to_string(lm35_res_1_Celsius_mv, lm35_res_1_txt);
        ret = Convert_short_to_string(lm35_res_2_Celsius_mv, lm35_res_2_txt);
        
        ret = lcd_8bit_send_string_pos(&lcd_1, 2, 8, lm35_res_1_txt);
        ret = lcd_8bit_send_string_pos(&lcd_1, 3, 8, lm35_res_2_txt);
        
        if(lm35_res_1_Celsius_mv > 30){
            ret = dc_motor_move_right(&dc_motor_1);
        }
        else{
            ret = dc_motor_stop(&dc_motor_1);
        }
        
        if(lm35_res_2_Celsius_mv > 40){
            ret = dc_motor_move_right(&dc_motor_2);
        }
        else{
            ret = dc_motor_stop(&dc_motor_2);
        }   
    }
    return (EXIT_SUCCESS);
}
/*
void application_intialize(void)
{
    std_ReturnType ret = E_OK;
   
    
} 
 */

