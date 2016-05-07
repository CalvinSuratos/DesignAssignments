;
; DA2-AssemblyLanguage.asm
;
; Created: 5/3/2016 5:34:04 PM
; Author : Calvin Suratos
;

 ;Header Files
 .INCLUDE "M328PDEF.INC"


.MACRO	INITSTACK
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16
.ENDMACRO


INITSTACK	;Use macro here

	SBI		DDRC, 0		;PC0 as output
	SBI		DDRC, 4		;PC4 as output
	SBI		DDRC, 5		;PC5 as output
	LDI		R16, 0x01	
	LDI		R17, 0x01	
	OUT		PORTC, R17	;Set PC0 high

	SBI		DDRD, 0		;PD0 as output
	SBI		DDRD, 1		;PD1 as output
	SBI		DDRD, 2		;PD2 as output
	SBI		DDRD, 3		;PD3 as output
	SBI		DDRD, 4		;PD4 as output
	SBI		DDRD, 5		;PD5 as output
	SBI		DDRD, 6		;PD6 as output
	SBI		DDRD, 7		;PD7 as output
	LDI		R18, 0x00
	OUT		PORTD, R18	;Set on low

	LDI		R19, 0x00	;Counter to 8-bit LED

	LDI		R21, 0		;Counter compare to 5
	LDI		R22, 0		;Counter compare to 10
	LDI		R23, 0x10	;For PC4
	LDI		R24, 0x20	;For PC5

BEGIN:
	RCALL	DELAY
	EOR		R17, R16	;Toggle DS of R17
	OUT		PORTC, R17	;Toggle PC0

	EOR		R18, R16	;Toggle DS of R18
	OUT		PORTD, R18	;Toggle PD0
	ADD		R19, R18	;Increment 
	OUT		PORTD, R19	;Toggle rest of PD

	INC		R21			;Increment counter for PC4
	INC		R22			;Increment counter for PC5

	CPI		R21, 10		;Compare to 5 rising pulse 
	BREQ	TOGPC4		;Branch if equal to 

GOBACK:
	RJMP	BEGIN		;Loop never ends

TOGPC4:
	EOR		R17, R23	;Toggle DS of R17
	OUT		PORTC, R17	;Toggle PC4
	LDI		R21, 0		;Reset counter for PC4
	CPI		R22, 20		;Compare to 10 rising pulse
	BREQ	TOGPC5		;Branch if equal to
	JMP		GOBACK		;Jump back to loop
	
TOGPC5:
	EOR		R17, R24	;Toggle DS of R17
	OUT		PORTC, R17	;Toggle PC5
	LDI		R22, 0		;Reset counter for PC5
	JMP		GOBACK		;Jump back to loop


DELAY:
	LDI		R20, 0x85
	STS		TCNT1H, R20	;Timer1 High = 0x85
	LDI		R20, 0xED
	STS		TCNT1L, R20	;Timer1 Low = 0xED
	LDI		R20, 0x00
	STS		TCCR1A, R20	;WGM11:10 = 00
	LDI		R20, 0x03
	STS		TCCR1B, R20	;WGM13:12 = 00, Normal Mode, Prescaler = 3

AGAIN:
	IN		R20, TIFR1	;Read TIFR
	SBRS	R20, TOV1	;If TOV1 is set skip next instruction
	RJMP	AGAIN		;Jump to again
	LDI		R20, 0x01
	STS		TCCR1B, R20	;Stop Timer1
	OUT		TIFR1, R20	;Clear TOV1 Flag
	RET