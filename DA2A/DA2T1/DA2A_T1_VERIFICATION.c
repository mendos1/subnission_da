;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;																						;;;;;;
;;;;	Assignment 2A part 1 C verification 																;;;;;;
;;;;																						;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#define F_CPU   16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	
	DDRB = 0X24;        //Set the PB2 and PB5 as an outputs
	PORTB |= (1<<5);	// turn off PB5 
	TCCR1B =4;			// set prescalar to 256
	
	while(1){
		TCNT1 = 0;					// reset timer counter 
		while(TCNT1 != 27187){}		// on delay 
		PORTB ^= 0X04;				// toggle LED 
		TCNT1 = 0;					// reset timer counter 
		while(TCNT1 != 18124){}		// off delay 
		PORTB ^= 0X04;				// toggle LED 
	}
	
}