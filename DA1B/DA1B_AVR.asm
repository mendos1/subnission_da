;
; DA1B.asm
;
; Created: 2/21/2019 4:18:14 PM
; Author : Rexaul
;

.equ	STARTADDS =	0X0200
.equ	CountOne = 99
;.equ	CountTwo = 3

.org 0x0000
	clr		r0
	ldi		xl, Low(STARTADDS)
	ldi		xh, high(STARTADDS)

	ldi		yl, low(0x0400)
	ldi		yh, high(0x0400)

	ldi		zl, low(0x0600)
	ldi		zh, high(0x0600)

	ldi		r21, CountOne
	ldi		r23, 11
	

START:
	mov		r22, r23
	st		X+, r23
	rjmp	CHECK		; check its divisibily to number 3

CHECK:
	subi	r22, 0x03
	brlt	NOTDIV
	breq	DIV
	rjmp	CHECK

DIV:
	st		Y+, r23
	add		r16, r23
	adc		r17, r0
	rjmp	END

NOTDIV:
	st		Z+, r23
	add		r18, r23
	adc		r19, r0
	rjmp	END

END:
	inc		r23
	dec		r21
	brne	START
	break 