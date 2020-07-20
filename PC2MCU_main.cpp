/*
 * PC2MCU.cpp
 *
 * Created: 06-07-2020 6.05.32 PM
 * Author : abhin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define Baud_Rate 9600
#define UBRR_value 103




void USART_INIT(void);
void sendstring( char *name);
void sendcharacter(unsigned char character);
void LCDstring(char *showname);
void LCDcharacter(unsigned  char showcharacter);



int main(void)
{  
	 USART_INIT();
	DDRC|=(1<<PINC0)|(1<<PINC1)|(1<<PINC2)|(1<<PINC3)|(1<<PINC4);
	PORTC&=~((1<<PINC0)|(1<<PINC1)|(1<<PINC2)|(1<<PINC3)|(1<<PINC4));
   sei();
   sendstring("Please choose one option \n");
   _delay_ms(10);
   sendstring(" R or r for RED LED \n");
   _delay_ms(10);
   sendstring(" Y or y for YELLOW LED \n");
   _delay_ms(10);
   sendstring(" B or b for BLUE LED \n");
   _delay_ms(10);
   sendstring(" G or g for GREEN LED \n");
   _delay_ms(10);
   sendstring(" W or w for WHITE LED \n");
   _delay_ms(10);
   sendstring(" waiting for response....\n");
    while (1) 
    {
	
		
    }
}
void USART_INIT(void)
{
	UCSR0B|=(1<<RXCIE0);
	UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
	UCSR0C|=(1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
	UBRR0H=(unsigned char)(UBRR_value>>8);
	UBRR0L=(unsigned char)(UBRR_value);
	
}
void sendstring(char *name)
{
	while(*name>0)
	{
		sendcharacter(*name ++);
	}
	
}
void sendcharacter(unsigned char character)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=character;
}


ISR(USART_RX_vect)
{
	unsigned char recieved_data = UDR0;
	switch(recieved_data)
	{
		case 'R':sendstring("you choose RED LED");
					 PORTC^=(1<<PINC0);
				  _delay_ms(100);
				  PORTC&=~(1<<PINC0);
				  break;
		case 'G': sendstring("you choose GREEN LED");
					PORTC^=(1<<PINC1);
				  _delay_ms(100);
				   PORTC&=~(1<<PINC1);
				  break;
		case 'B':sendstring("you choose BLUE LED");
				PORTC^=(1<<PINC2);
				_delay_ms(100);
				 PORTC&=~(1<<PINC2);
				break;
		case 'Y':sendstring("you choose YEllOW LED"); 
				PORTC^=(1<<PINC3);
				_delay_ms(100);
				 PORTC&=~(1<<PINC3);
				break;
		case 'W':sendstring("you choose WHITE LED");
				PORTC^=(1<<PINC4);
				_delay_ms(100);
				PORTC&=~(1<<PINC4);
				break; 
		case 'r':sendstring("you choose RED LED");
				 PORTC^=(1<<PINC0);
				_delay_ms(100);
				PORTC&=~(1<<PINC0);
				break;
		case 'g': sendstring("you choose GREEN LED");
				PORTC^=(1<<PINC1);
				_delay_ms(100);
				PORTC&=~(1<<PINC1);
				
				break;
		case 'b':sendstring("you choose BLUE LED"); 
				PORTC^=(1<<PINC2);
				_delay_ms(100);
				PORTC&=~(1<<PINC2);
				break;
		case 'y':sendstring("you choose YEllOW LED");
				 PORTC^=(1<<PINC3);
				_delay_ms(100);
				PORTC&=~(1<<PINC3);
				break;
		case 'w': sendstring("you choose WHITE LED");
				PORTC^=(1<<PINC4);
				_delay_ms(100);
				PORTC&=~(1<<PINC4);
				break;
		default : sendstring("sorry wrong key pressed");
				PORTC&=~((1<<PINC0)|(1<<PINC1)|(1<<PINC2)|(1<<PINC3)|(1<<PINC4));
				break;
	}
	
}