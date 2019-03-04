;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;																						;;;;;;
;;;;	Assignment 2A part 1 Blinking LED with 60% duty cycle with period of 0.725 seconds	;;;;;;
;;;;																						;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Replace with your application code
; Replace with your application code
.org	0x0000
    ;Initialize the microcontroller stack pointer
	ldi		r16, 0x24		; setting pd2
	out		DDRB, r16			; enableing pd2 as output
	ldi		r16, 0x04		; setting pd2
	ldi		r17, 0x20		; used to set/reset pd5
	//out		PORTB, r17		; setting port to off
	
	ldi		r20, 0x04		; setting up TCCR1B = 00000101 for 256
	sts		TCCR1B,	r20 
begin:
	ldi		r20, 0x00		; setting up timer counter to 0
	sts		TCNT1H, r20 	; Timer counter is 16 bits
	sts		TCNT1L, r20 	; Thus, requires 2 8 bit regs
	rjmp	delay_onnnnn 	; routine for on delay (remember multi function
							; table is reverse logic 
returnOne:
	eor		r17, r16		; xor to toggle LED
	out		PORTB, r17		; enable pd5
	ldi		r20, 0x00		; setting up timer counter to 0
	rjmp	delay_offffff 	; routine call for 4 second delay see below 
returnTwo:
	eor		r17, r16		; xor to toggle LED
	out		PORTB, r17		; enable pd5

	rjmp	begin			; repeat main loop

delay_onnnnn:
	lds		r29, TCNT1H		; load upper bytes of timer counter to r29
	lds		r28, TCNT1L 	; load lower bytes of timer counter to r28

	cpi		r28, 0xCC		; check to see if lower 8 bits of timer counter are 0x08
	brsh	body1
	rjmp	delay_onnnnn	; otherwise keep checking lower bytes

body1:
	cpi		r29, 0x46		; check if upper timer counter have reached desired value
	brlt	delay_onnnnn	; otherwise recheck the lower bytes
	rjmp returnOne

delay_offffff:
	lds		r29, TCNT1H		; load upper bytes of timer counter to r29
	lds		r28, TCNT1L 	; load lower bytes of timer counter to r28

	cpi		r28, 0x33		; check to see if lower 8 bits of timer counter are 0x08
	brsh	body2
	rjmp	delay_offffff	; otherwise keep checking lower bytes

body2:
	cpi		r29, 0x6A		; check if upper timer counter have reached desired value
	brlt	delay_offffff	; otherwise recheck the lower bytes
	rjmp returnTwo
	