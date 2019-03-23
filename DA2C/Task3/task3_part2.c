#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t tof_detected;

ISR( TIMER0_COMPA_vect ){
	TCNT0 = 0;
	int counter = 0;
	if(!(PINC & (1<<PINC1) ) ){
		while(counter < 77){
			while((TIFR0 & (1<<OCF0A) ) == 0){
				PORTB &= ~(1<<2);
			}
			TCNT0 = 0;
			TIFR0 |= (1<<OCF0A);
			counter++;
		}
		counter = 0;
	}
	else{
		PORTB |= (1<<2);
	}
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
