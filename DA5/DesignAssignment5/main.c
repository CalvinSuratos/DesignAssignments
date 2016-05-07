/*
 * DesignAssignment5.c
 *
 * Created: 4/21/2016 10:10:08 AM
 * Author : Calvin Suratos
 */ 

#pragma region DC Motor Code

#define F_CPU 8000000UL			//XTAL = 8MHZ
#define ENABLE 1				//Enable pin 1
#include <avr/io.h>				//Defines pins, ports, etc.
#include <util/delay.h>			//Defines delay

static inline void initADC0(void) 
{
	ADMUX |= (1 << REFS0);									//Reference voltage on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	//ADC clock prescaler /8
	ADCSRA |= (1 << ADEN);									//Enables the Analog digital converter (ADC)
}

int main(void) 
{
	int16_t potentiometerValue;		//Compare Potentiometer Value to certain number ranges
		
	DDRC |= (1 << ENABLE);			//Data Direction Register C: writing a 1 to the bit enables output

	initADC0();						//Initialize ADC0

	while (1) 
	{
		ADCSRA |= (1 << ADSC);						//Start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);		//Wait until ADC conversion is done
		potentiometerValue= ADC;					//Read ADC value in
		
		if (potentiometerValue >= 0  && potentiometerValue < 250) 
		{
			//100% duty cycle 
			PORTC = PORTC | (1<<ENABLE);
			_delay_ms(0);				
			PORTC = PORTC & (~(1<<ENABLE));
			_delay_ms(100);
		}
		else if (potentiometerValue >= 250 && potentiometerValue < 500)
		{
			//75% duty cycle 
			PORTC = PORTC | (1<<ENABLE);
			_delay_ms(25); 
			PORTC = PORTC & (~(1<<ENABLE));
			_delay_ms(100);
		}
		else if (potentiometerValue >= 500 && potentiometerValue < 750) 
		{
			//50% duty cycle pulse
			PORTC = PORTC | (1<<ENABLE);
			_delay_ms(100); 
			PORTC = PORTC & (~(1<<ENABLE));
			_delay_ms(100);
		}
		else 
		{
			//0% duty cycle pulse
			PORTC = PORTC | (1<<ENABLE);
			_delay_ms(0); 
		}
	}
	return (0);		//Never reached
}

#pragma endregion DC Motor Code

#pragma region Stepper Motor Code

#define F_CPU 8000000UL		//XTAL = 8MHZ
#define ENABLE 1			//Enable pin 1
#include <avr/io.h>			//Defines pins, ports, etc.
#include <util/delay.h>		//Defines Delay

static inline void initADC0(void) 
{
	ADMUX |= (1 << REFS0);										//reference voltage on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);		//ADC clock prescaler /8
	ADCSRA |= (1 << ADEN);										//enables the ADC
}

int main()
{
	DDRC = 0x02;	//Set Port C Pin 1 to output and the rest input
	DDRB = 0xFF;	//Set Port B of all pins to output

	int16_t potentiometerValue;	//Compare Potentiometer Value to certain number ranges
	
	initADC0();					//Initialize ADC0

	while (1)
	{
		ADCSRA |= (1 << ADSC);					//Start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);	//Wait until ADC conversion is done
		potentiometerValue = ADC;				//Read ADC value in

		if ((PINC  & 0x08) == 0)
		{
			if (potentiometerValue >= 0  && potentiometerValue < 250)
			{
				//75 speed
				PORTB = 0x66;
				_delay_ms(75);
				PORTB = 0xCC;
				_delay_ms(75);
				PORTB = 0x99;
				_delay_ms(75);
				PORTB = 0x33;
				_delay_ms(75);
			}
			else if (potentiometerValue >= 250 && potentiometerValue < 500)
			{
				//120 speed
				PORTB = 0x66;
				_delay_ms(115);
				PORTB = 0xCC;
				_delay_ms(115);
				PORTB = 0x99;
				_delay_ms(115);
				PORTB = 0x33;
				_delay_ms(115);
			}
			else if (potentiometerValue >= 500 && potentiometerValue < 750)
			{
				//165 speed
				PORTB = 0x66;
				_delay_ms(165);
				PORTB = 0xCC;
				_delay_ms(165);
				PORTB = 0x99;
				_delay_ms(165);
				PORTB = 0x33;
				_delay_ms(165);
			}
			else
			{
				//190 speed
				PORTB = 0x66;
				_delay_ms(190);
				PORTB = 0xCC;
				_delay_ms(190);
				PORTB = 0x99;
				_delay_ms(190);
				PORTB = 0x33;
				_delay_ms(190);
			}
		}
		else
		{
			if (potentiometerValue >= 0  && potentiometerValue < 250)
			{
				//75 speed
				PORTB = 0x66;
				_delay_ms(75);
				PORTB = 0x33;
				_delay_ms(75);
				PORTB = 0x99;
				_delay_ms(75);
				PORTB = 0xCC;
				_delay_ms(75);
			}
			else if (potentiometerValue >= 250 && potentiometerValue < 500)
			{
				//120 speed
				PORTB = 0x66;
				_delay_ms(120);
				PORTB = 0x33;
				_delay_ms(120);
				PORTB = 0x99;
				_delay_ms(120);
				PORTB = 0xCC;
				_delay_ms(120);
			}
			else if (potentiometerValue >= 500 && potentiometerValue < 750)
			{
				//165 speed
				PORTB = 0x66;
				_delay_ms(165);
				PORTB = 0x33;
				_delay_ms(165);
				PORTB = 0x99;
				_delay_ms(165);
				PORTB = 0xCC;
				_delay_ms(165);
			}
			else
			{
				//190 speed
				PORTB = 0x66;
				_delay_ms(190);
				PORTB = 0x33;
				_delay_ms(190);
				PORTB = 0x99;
				_delay_ms(190);
				PORTB = 0xCC;
				_delay_ms(190);
			}
		}
	}
	
	return (0);	//Never reached
}

#pragma endregion Stepper Motor Code

#pragma region Servo Motor Code

#define F_CPU 8000000UL		//XTAL = 8MHZ
#define ENABLE 1			//Enable pin 1
#include <avr/io.h>			//Defines pins, ports, etc.
#include <util/delay.h>		//Defines Delay

static inline void initADC0(void)
{
	ADMUX |= (1 << REFS0);										//reference voltage on AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);		//ADC clock prescaler /8
	ADCSRA |= (1 << ADEN);										//enables the ADC
}

int main()
{
	uint16_t potentiometerValue;		//Compare Potentiometer Value to certain number ranges
	initADC0();							//Initialize ADC

	DDRD=0x00;		//Port D pins as input
	PORTD=0xFF;		//Enable internal pull ups
	DDRB=0xFF;		//Set PORTB1 pin as output
	
	//Output compare OC1A 8 bit non inverted PWM
	//Clear OC1A on Compare Match, set OC1A at TOP
	ICR1=20000;	//ICR1=20000 defines 50Hz PWM, TOP=ICR1;
	TCCR1A|=(0<<COM1A0)|(1<<COM1A1)|(0<<COM1B0)|(0<<COM1B1)|(0<<FOC1A)|(0<<FOC1B)|(1<<WGM11)|(0<<WGM10);
	TCCR1B|=(0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);	//Start timer with prescaler 8

	OCR1A = 0;

	for (;;)
	{
		ADCSRA |= (1 << ADSC);					//Start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);	//Wait until ADC conversion is done
		potentiometerValue = ADC;				//Read ADC in


		OCR1A = 1200 + (potentiometerValue*3.4);	//Every turn = 180 degrees of servo
	}
}


#pragma endregion Servo Motor Code