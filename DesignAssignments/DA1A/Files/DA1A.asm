; 
;	Student Name: Saul Alejandro Mendoza Guzman 
;	Student #: 2000540481
;	Student Email: mendos1@unlv.nevada.edu
;
.org 0x0000 
	
	ldi		r16, 0x08		; Decrementing counter control
	clr		r18			; Product Low Bytes
	clr		r19			; Product Mid Bytes
	clr		r20			; Product High Bytes
	ldi		r21, 0x00		; Always Zero
	ldi		r22, 0xFF		; Plier
	ldi		r23, 0x00		; Virtual High Bytes for Cand
	ldi		r24, 0xFF		; Cand Low Bytes
	ldi		r25, 0xFF		; Cand Mid Bytes

BitCheck:
	
	mov		r17, r22		; Bit Checking Register 
	andi	r17, 0b00000001			; Logical AND Bit Check Set Up
	brne	AddCandStage		; 1 Is Detected As First Bit
	breq	ShiftStage		; 0 Is Detected As First Bit

ShiftStage:

	lsl		r23			; Logical Shift Left Of Virtual Bytes
	lsl		r25			; Logical Shift Left Of High Bytes of Cand
	adc		r23, r21		; Add Carry Bit Of Previouse Step To Virtual Bytes Of Cand
	lsl		r24			; Logical Shift Left Of Low Bytes Of Cand
	adc		r25, r21		; Add Carry Bit of Previouse Step To High Bytes
	
	lsr		r22			; Logical Shift Right Of Plier
	dec		r16			; Decrement Bit/Shift Counter
	brne	BitCheck		; If Not Zero Branch To Label BitCheck
	breq	Done		; If Zero Branch To Label Done

AddCandStage:

	add		r18, r24		; Add Low Bytes Of Product And Cand respectively
	adc		r19, r21		; Add Carry Bit To Mid Reg Of Product
	adc		r20, r21		; Add Propagated Bit To High Bytes of Product
	add		r19, r25		; Add Mid/High Bytes of Product And Cand Respectively
	adc		r20, r21		; Add Carry Bit to Higher 
	add		r20, r23		; Add High Byte of Product with Virtual Byte of Cand

	rjmp	ShiftStage

Done:
	
	BREAK

	.org 0x0000
ldi		r16, 0x08		; Decrementing counter control
	clr		r18			; Product Low Bytes
	clr		r19			; Product Mid Bytes
	clr		r20			; Product High Bytes
	ldi		r21, 0x00		; Always Zero
	ldi		r22, 0xFF		; Plier
	ldi		r23, 0x00		; Virtual High Bytes for Cand
	ldi		r24, 0xFF		; Cand Low Bytes
	ldi		r25, 0xFF		; Cand Mid Bytes

	mul 		r22, r24 		
	add 		r18, r0
 	adc 		r19, r1
	adc 		r20, r16
	
	mul 		r22, r25
 	add 		r19, r0
 	adc 		r20, r1

Done:
	
	BREAK