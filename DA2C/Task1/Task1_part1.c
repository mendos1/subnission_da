#define F_CPU 16000000UL
#include <avr/io.h>
// THIS IS TASK1 PART1
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void){
	DDRB = 36;
	PORTB |= (1<<5);
	TCCR0B = 5;
	while(1){
		TCNT0 = 0;
		int TACO = 0;
		while(TACO != 27){
			while(TCNT0 != 255);
			TCNT0 = 0;
			TACO++;
		}
		PORTB ^= (1<<2);
		TACO = 0;
		TCNT0 = 0;
		while(TACO != 18){
			while(TCNT0 != 255);
			TCNT0 = 0;
			TACO++;
		}
		PORTB ^= (1<<2);
		TACO = 0;
		TCNT0 = 0;
	}
}