#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile uint8_t tof_detected;

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect){
	// keep a track of number of overflows
	tof_detected++;
}

void timer0_init(){
	// set up timer with prescaler = 1024
	TCCR0B |= (1 << CS02)|(1 << CS00);
	
	// initialize counter
	TCNT0 = 0;
	TIMSK0 |= (1 << TOIE0);
	sei(); 
	tof_detected = 0;
}
void of_funct(unsigned int of_detection_num, unsigned int tcount){
	// check if no. of overflows = of_detection_num
	if (tof_detected >= of_detection_num){
		// NOTE: '>=' is used
		// check if the timer count reaches tcount
		
		if (TCNT0 >= tcount){
			PORTB ^= (1 << 2);    // toggles the led
			TCNT0 = 0;            // reset counter
			tof_detected = 0;     // reset overflow  detection counter
		}
	}
}
int main(void){
	// connect led to pin PB2
	DDRB |= (1 << 2);
	DDRB |= (1 << 5);
	PORTB ^= (1 << 5);    // toggles the led off
	
	// initialize timer
	timer0_init();
	
	// loop forever
	while(1){
		of_funct(26, 165);
		of_funct(17, 195);
	}
}