;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;																						;;;;;;
;;;;	Assignment 2A part 2 																;;;;;;
;;;;																						;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Replace with your application code

.org 0x0000

		CBI		DDRC, 1		; MAKE PC1 = 0 AN INPUT
		SBI		DDRB, 2		; MAKE PB2 = 1 AN OUTPUT
		SBI		DDRB, 5		; MAKE PB5 AN OUTPUT
		SBI		PORTB, 5	; TURN OFF D1(PB5) LED
		SBI		PORTB, 2	; TURN OFF D4(PB2) LED

AGAIN:	
		SBIC	PINC, 1	; SKIP IF BIT PC1 IS HIGH	
		RJMP	AGAIN		; JUMP TO "OVER" IF PC1 != 0
		// SET UP SUBROUTINE FOR LED TO STAY ON FOR 1.25 SECONDS
		RCALL	TLED_ON		; CALL SUBROUTINE TO KEEP LED ON FOR 1.25 SECONDS
RETURN:
		RJMP	AGAIN		; JUMP BACK TO READ PC1	
		SBI		PORTB, 2	; PB2 =1, THAT IS, ITS OFF
		RJMP	AGAIN		; GO BACK TO READ PC1

TLED_ON:
		CBI		PORTB, 2	; PB2 = 0, THAT IS, ITS ON
		LDI		R20, 0X05	; SET PRESCALAR TO 1024
		STS		TCCR1B, R20 ; 
		LDI		R20, 0X00	; SET UP TIMER1 CLEAR
		STS		TCNT1H, R20	; CLEAR UPPER TIMER COUNTER NIBLE
		STS		TCNT1L, R20 ; CLEAR LOWER TIMER COUNTER NIBLE
		RJMP	DELAY_ON	; START DELAY ROUTINE
DELAY_ON:
		LDS		R29, TCNT1H		; load upper bytes of timer counter to r29
		LDS		R28, TCNT1L 	; load lower bytes of timer counter to r28
		CPI		R28, 0x4A		; check to see if lower 8 bits of timer counter are 0x08
		BRSH	BODY
		RJMP	DELAY_ON		; otherwise keep checking lower bytes
BODY:	
		CPI		R29, 0x4C		; check if upper timer counter have reached desired value
		BRLT	DELAY_ON		; otherwise recheck the lower bytes
		SBI		PORTB, 2		; TURN OFF LED
		RET