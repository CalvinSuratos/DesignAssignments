/* Nokia 5110 LCD AVR Library example
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 */
/*
Calvin Suratos
Design Assignment 6	
*/

//Header Files
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "Nokia5110.h"

//Initialize Analog Digital Converter
static inline void initADC0(void) {
	ADMUX |= (1 << REFS0);									//Reference AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	//Prescaler 8
	ADCSRA |= (1 << ADEN);									//Enables ADC
}

int main(void)
{
	DDRC |= (1<<PB4);		//Output LED to PB4
	PORTC |= (1<<PB4);		//Turn LED PB4 on

	int16_t Temp;	//Value of temperature
	float VO;				//Voltage Output
	float Fah;				//Fahrenheit
	float Cel;				//Celsius
	char BuffF[200];		//Fahrenheit Buffer				
	char BuffC[200];		//Celsius Buffer

	initADC0();				//Initialize ADC
	nokia_lcd_init();		//Initialize Nokia LCD. In library

	while (1)
	{
		ADCSRA |= (1 << ADSC);					//Start conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);	//Wait until finish
		Temp = ADC;								//Store in temperature value

		VO = (Temp / 1024.0) * 5000;	//Equation for voltage output
		Fah = VO / 10;					//Equation for Fahrenheit
		Cel = (Fah - 32) * (5.0 / 9.0);	//Equation for Celsius

		sprintf(BuffF,"%.1f", Fah);		//Store into Buffer F
		sprintf(BuffC,"%.1f", Cel);		//Store into Buffer C
		
		nokia_lcd_clear();					//Clear LCD
		nokia_lcd_write_string("Temperature:", 1);
		nokia_lcd_set_cursor(0, 10);		//Set cursor position F
		nokia_lcd_write_string(BuffF, 2);	//Display Fahrenheit
		nokia_lcd_write_string(" F", 2);	//Display Unit F
		nokia_lcd_set_cursor(0, 25);		//Set cursor position C
		nokia_lcd_write_string(BuffC, 2);	//Display Celsius
		nokia_lcd_write_string(" C", 2);	//Display Unit C
		nokia_lcd_render();

		_delay_ms(1000);
	}
}
