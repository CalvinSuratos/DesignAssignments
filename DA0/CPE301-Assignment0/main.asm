;
; CPE301-Assignment0.asm
;
; Created: 2/15/2016 4:27:04 PM
; Author : Calvin Suratos
;


.INCLUDE "M328PDEF.INC"

	LDI		R16, 35		; R16 = 35
	LDI		R17, 40		; R17 = 40
	LDI		R18, 45		; R18 = 45
	LDI		R19, 50		; R19 = 50
	LDI		R20, 55		; R20 = 55

	LDI		R22, 0xFF	; R22 = 0xFF = 0b11111111
	OUT		DDRB, R6	; Make Port B an output port (1111 1111)

	ADD		R21, R16	; R21 = R21 + R16
	BRVS	OfJmp		; Branch if there is an overflow (V = 1)
	ADD		R21, R17	; R21 = R21 + R17
	BRVS	OfJmp		; Branch if there is an overflow (V = 1)
	ADD		R21, R18	; R21 = R21 + R18
	BRVS	OfJmp		; Branch if there is an overflow (V = 1)
	ADD		R21, R19	; R21 = R21 + R19
	BRVS	OfJmp		; Branch if there is an overflow (V = 1)
	ADD		R21, R20	; R21 = R21 + R20
	BRVS	OfJmp		; Branch if there is an overflow (V = 1)

	CBI		PORTB, 2	; Clear bit PB2
	RJMP	Done		; Branch to done to finish program

OfJmp:
	SBI		PORTB, 2	; Set bit PB2

Done:
