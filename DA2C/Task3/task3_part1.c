#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t tof_detected;

ISR( TIMER0_COMPA_vect ){
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
void timer0_init(){
	// set up timer with prescaler = 1024
	TCCR0B |= (1 << CS02)|(1 << CS00);
	
	// initialize counter
	TCNT0 = 0;
	TIMSK0 |= (1 << OCIE0A);
	sei();
	tof_detected = 0;
}

int main(void){
	DDRB |= (1 << 2);
	DDRB |= (1 << 5);
	PORTB ^= (1 << 5);    // toggles the led off
	timer0_init();

	while(1);
}