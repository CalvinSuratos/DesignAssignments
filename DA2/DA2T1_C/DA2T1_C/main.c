/*
 * DA2T1_C.c
 *
 * Created: 3/10/2016 11:56:07 AM
 * Author : Calvin
 */ 

#include <avr/io.h>


int main(void)
{
    DDRC = 1 << 0;
	PORTC &= ~ (1<<0);
    while (1) 
    {
		OCR1A = 0x3D09;
		TCCR1A = 0x00;
		TCCR1B = 0x0C;
		while ((TIFR1&(1<<OCF1A)) == 0)
		{
			TIFR1 = 0x02;
			PORTC =  PORTC ^ (1<<0);
		}
    }
}

