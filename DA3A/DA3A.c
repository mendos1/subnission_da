#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER ( (F_CPU /BAUDRATE/16UL) - 1)

// Function Declarations
void USART_init( unsigned int ubrr );
void USART_tx_string( char *data );
//volatile float adc_temp = 7.2543;
char outs[20];

int main(void)
{
	float adc_temp = 7.2543;
	USART_init(BAUD_PRESCALLER);		// Initialize the USART
	USART_tx_string("Connected!\r\n");	// we're alive!
	_delay_ms(125);						// wait a bit
	while(1)
	{
		 sprintf(outs, "adc_temp = %.4f\r\n", adc_temp);
		USART_tx_string(outs);								// 
		_delay_ms(2000);									// wait a bit
	}
}

/* INIT USART (RS-232)  */
void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable UART receiver and transmitter */
	UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //asynchronous 8 N 1
}

/* SEND A STRING TO THE RS-232 */
void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}