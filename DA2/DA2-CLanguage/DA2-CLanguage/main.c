/*
 * DA2-CLanguage.c
 *
 * Created: 5/3/2016 11:52:06 PM
 * Author : Calvin Suratos
 */ 

//Header Files
#include <avr/io.h>


int main(void)
{
    DDRC |= (1 << PC0) | (1 << PC4) | (1 << PC5);	//PC0, PC4, PC5 as output
    PORTC &= ~ (1<<0);								//Set PC0 high

	DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7); //PD0-PD7 as output
	PORTD = 0;	//Set on low

	uint8_t Reg19 = 0x00;	//Counter for 8-bit

	uint8_t Reg16 = 0x01;
	uint8_t Reg17 = 0x01;
	uint8_t Reg18 = 0x00;

	uint8_t CountPC4 = 0;	//Counter compare to 5
	uint8_t CountPC5 = 0;	//Counter compare to 10

	uint8_t Reg23 = 0x10;	//For PC4
	uint8_t Reg24 = 0x20;	//For PC5

    while (1)
    {
	    TCNT1 = 0x85ED;		//Timer1 = 0x85ED
	    TCCR1A = 0x00;		//WGM11:10 = 00
	    TCCR1B = 0x03;		//WGM13:12 = 00, Normal Mode, Prescaler = 3
		
	    while ((TIFR1&(1<<TOV1)) == 0);		//Read TIFR, if TOV1 is set skip next instruction
	    TCCR1B = 0x01;						//Stop Timer1
	    TIFR1 |= (1<<TOV1);					//Clear TOV1 Flag

		Reg17 ^= Reg16;			//Toggle R17 using EOR
	    PORTC = Reg17;			//Toggle PC0

		Reg18 ^= Reg16;			//Toggle R18 using EOR
		PORTD = Reg18;			//Toggle PD0
		Reg19 = Reg19 + Reg18;	//Increment counter
		PORTD = Reg19;			//Toggle rest of PD

		CountPC4++;		//Increment counter for PC4
		CountPC5++;		//Increment counter for PC5

		if (CountPC4 == 10)			//Compare to 5 rising pulse
		{
			Reg17 ^= Reg23;			//Toggle R17 using EOR
			PORTC = Reg17;			//Toggle PC4
			CountPC4 = 0;			//Reset counter for PC4
			if (CountPC5 == 20)		//Compare to 10 rising pulse
			{
				Reg17 ^= Reg24;		//Toggle R17 using EOR
				PORTC = Reg17;		//Toggle PC5
				CountPC5 = 0;		//Reset counter for PC5
			}
		}
    }
}
