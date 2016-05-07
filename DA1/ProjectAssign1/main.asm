;
; ProjectAssign1.asm
;
; Created: 2/25/2016 12:39:27 PM
; Author : Calvin
;

.INCLUDE "M328PDEF.INC"

.MACRO INITSTACK
	LDI		R16, HIGH(RAMEND)
	LDI		R16, LOW(RAMEND)
.ENDMACRO

INITSTACK				; Use Macro Here
	LSR		R16			; Shift right, same as div/2
	LDI		R17, 0x19	; Counter for 25 Values
	LDI		R18, 0x01	; Get first value
	ST		R16, R18	; R18 to mem location

LoadNum:
	INC		R16			; Increment low byte of SPL
	INC		R18			; Get next value 
	ST		R16, R18	; Store next value
	DEC		R17			; Decrement counter
	BRNE	LoadNum		; Loop until counter = zero


BEGIN:
	RCALL	DELAY
	EOR		R17,R16		;toggle D5 of R17;
	OUT		PORTB,R17	;toggle PB5
	RJMP	BEGIN

;TIMER1 DELAY
DELAY:
	LDI		R20,0xA4	;LDI R20, 0x85
	STS		TCNT1H,R20	;TCNT1H = 0xD8 timer1 high
	LDI		R20,0x72	;LDI R20, 0xED
	STS		TCNT1L,R20	;TCNT1L = 0xF0 timer1 low
	LDI		R20,0x00
	STS		TCCR1A,R20	;WGM11:10 = 00 ;LDI R20,0x04
	LDI		R20, 0x05
	STS		TCCR1B,R20	;WGM13:12 = 00, Normal mode, prescaler = 1

AGAIN:
	IN		R20,TIFR1	;read TIFR
	SBRS	R20,TOV1	;if TOV1 is set skip next instruction
	RJMP	AGAIN
	LDI		R20, 0x01
	OUT		TIFR1, R20
	STS		TCCR1B,R20	;stop Timer1
	RET