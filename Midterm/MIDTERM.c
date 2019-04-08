#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile unsigned int Temperature;
char outs[256]; // OUTPUT ARRAY


volatile char Data_Received;

void usart_send(unsigned char ASCII){ //SEND DATA TO USART
	while(!(UCSR0A & (1<<UDRE0 )));
	UDR0 = ASCII;
}

unsigned char usart_receive(void){  //RECEIVE DATA
	while(!(UCSR0A & (1<< RXC0)));
	return Data_Received;
}


void adc_init(void) //INITIALIZE ADC
{
	
	ADMUX = (0<<REFS1)| // REFERENCE SELECTION BITS

	(1<<REFS0)| // AVcc - external cap at AREF
	(0<<ADLAR)| // ADC Left Adjust Result
	(0<<MUX2)|  // ANalog Channel Selection Bits
	(1<<MUX1)|  // ADC2 (PC2 PIN25)
	(0<<MUX0);  //

	ADCSRA = (1<<ADEN)| // ADC ENable

	(0<<ADSC)|  // ADC Start Conversion
	(0<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)|  // ADC Interrupt Flag
	(0<<ADIE)|  // ADC Interrupt Enable
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(0<<ADPS1)| //
	(1<<ADPS0); //

	TIMSK1 |= (1<<TOIE1); // enable overflow interrupt
	TCCR1B |= (1<<CS12)|(1<<CS10); // native clock
	TCNT1 = 49911; 

}


void read_adc(void) {
	unsigned char i =4;
	Temperature = 0; // INITIALIZE
	while (i--) {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		Temperature+= ADC;
		_delay_ms(50);
	}
	Temperature = Temperature / 8; // SAMPLING

}

/* INIT USART (RS-232) */
void USART_init( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0)| ( 1 << RXCIE0); // Enable receiver, transmitter & RX interrupt
	UCSR0C |= (1<<UCSZ01) | (1 << UCSZ00);
}

void USART_tx_string( char *data ) {
	while ((*data != '\0')) {
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}

int main(void) {
	adc_init(); // INITIALIZE THE ADC 
	USART_init(MYUBRR); // INITIALIZE THE RS232 interface
	_delay_ms(500); // WAIT 500ms
	sei(); // ENABLE GLOBAL INTERRUPTS

	
	while(1){}
}

ISR(TIMER1_OVF_vect) // TIMER OVERFLOW INTERRUPT TO DELAY 
{
	char TEMP[256];
	unsigned char AT[] = "AT\r\n"; 				//AT Commands
	unsigned char CWMODE[] = "AT+CWMODE=1\r\n"; //Set MODE
	unsigned char CWJAP[] = "AT+CWJAP=\"iPXSMax\",\"12345678\"\r\n"; //MUST CHANGE WIFI AND PASSWORD
	unsigned char CIPMUX[] = "AT+CIPMUX=0\r\n";
	unsigned char CIPSTART[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";
	unsigned char CIPSEND[] = "AT+CIPSEND=100\r\n";

	_delay_ms(2000);
	USART_tx_string(AT); // SEND COMMANDS
	
	_delay_ms(5000);
	USART_tx_string(CWMODE); // SET MODE
	
	_delay_ms(5000);
	USART_tx_string(CWJAP); // CONNECT TO WIFI
	
	_delay_ms(15000);
	USART_tx_string(CIPMUX); // MUX SELECTION
	
	_delay_ms(10000);
	USART_tx_string(CIPSTART);// CONNECT TCP
	
	_delay_ms(10000);
	USART_tx_string(CIPSEND);// SEND SIZE
	
	_delay_ms(5000);
	
	
	PORTC^=(1<<5);
	read_adc(); 			// READ ADC
	snprintf(outs,sizeof(outs),"GET https://api.thingspeak.com/update?api_key=Q099IRW0GDEGZYYV&field2=%3d\r\n", Temperature);// print it
	USART_tx_string(outs); // SEND DATA
	_delay_ms(10000);
	TCNT1 = 49911; 			//reset
	
}