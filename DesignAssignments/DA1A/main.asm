; 
;	Student Name: Saul Alejandro Mendoza Guzman 
;	Student #: 2000540481
;	Student Email: mendos1@unlv.nevada.edu
;

.org	0x0000

	ldi		r24, 0x11		; This is the 
	ldi		r25, 0x11		; Multiplicand

	ldi		r22, 0x11		; This is the multiplier 

	ldi		r16, 0x08		; This is the # of shifts 

	clr		r18				; This is where the
	clr		r19				; Result of the
	clr		r20				; Program will be stored

	clr		r21				; This is always Zero

ShiftCheck:
	cpi		r16, 0x00		; Compare reg 16 to 0
	brne	CheckLP			; If reg 16 is not equal to 0 we branch
	jmp	Done				; If they are equal we are done

CheckLP:
	mov		r17, r22		; Temp reg with value of r22
	andi	r17, 0b00000001	; Clear all bits besides the first one
							; To check for 1 or 0 in bit one

	cpi		r17, 0b00000001	; Compare first bits
	breq	AddCand			; If equal: branch to label "AddCand"
	brne	ShiftStage		; If !equal: branch to label "ShiftStage"

AddCand:
	add		r18, r24		; Add low bits
	adc		r19, r25		; Add mid bits with carry bit
	adc		r20, r21		; Add high bits with carry bit

ShiftStage:
	lsl		r25				; Logic Shift Left of reg 25
	lsl		r24				; Logic Shift Left of reg 24
	adc		r25, r21		; Add carry bit to reg 25. r21 is Zero
	lsr		r22				; Logic Shift Right of reg 22
	dec		r16				; Decriment r16 
	rjmp	ShiftCheck		; Relative Jump to "ShiftCheck" 

Done:						; Done
	BREAK
 