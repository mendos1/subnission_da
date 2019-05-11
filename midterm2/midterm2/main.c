/*				Main.c File				 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c_master.h"
#include "uart.h"
#include "apds.h"

// This is used to set up a filestream to use UART_string
FILE UART_string = FDEV_SETUP_STREAM(uart_putchar, NULL , _FDEV_SETUP_WRITE);

// This array of chars is where we will store our result
char The_Result[256];

int main(void)
{
	// red, green, and blue are the rgb components that we want. 
	uint16_t red = 0, green = 0, blue = 0;
	
	// Initialize I2C communication protocol
	i2c_init();
	
	// Initialize UART communication protocol
	init_UART();
	
	// variable used for UART string streaming
	stdout = &UART_string;
	
	// Initialize APDS device
	APDS_init();
	
 	_delay_ms(2000);
	printf("AT\r\n");	
	_delay_ms(5000);
	printf("AT+CWMODE=1\r\n"); 	
	_delay_ms(5000);
	printf("AT+CWJAP=\"Pornhub.com\",\"xoxo123\"\r\n");	
    while (1) 
    {
		_delay_ms(5000);
		printf("AT+CIPMUX=0\r\n");
		
		_delay_ms(5000);
		printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
		
		_delay_ms(5000);
		RGB_reader(&red, &green, &blue);
		printf("AT+CIPSEND=104\r\n");
		printf("GET https://api.thingspeak.com/update?api_key=Q099IRW0GDEGZYYV&field1=0%05u&field2=%05u&field3=%05u\r\n", red, green, blue);
		
		_delay_ms(3000);
    }
}


