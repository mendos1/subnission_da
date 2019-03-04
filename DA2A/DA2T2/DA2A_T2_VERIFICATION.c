;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;																						;;;;;;
;;;;	Assignment 2A part 2 C verification													;;;;;;
;;;;																						;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		
/* Created: 3/3/2019 1:18:18 PM
* Author : mendos1
*/ 
#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB |= (1<<2);		// set PB2 as output 
	PORTB |= (1<<5);	// turn off PB5 LED 
	DDRC &= (0<<1);		// set DATA REG C TO READ 
	PORTC |= (1<<1);	// 

    while (1) 
    {
		if(!(PINC & (1<<PINC1))){
			PORTB &= ~(1<<2);	// TOGGLE LED TO ON 
			_delay_ms(1250);	// WAIT 1.25 SECONDS 
		}
		else
			PORTB |= (1<<2);	// OTHERWISE STAY OFF 
    }
	return 0;
}
	