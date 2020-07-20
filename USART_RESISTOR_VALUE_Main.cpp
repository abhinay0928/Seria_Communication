/*
 * USART_Resistor_Value.cpp
 *
 * Created: 03-07-2020 6.45.24 PM
 * Author : abhin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

#define LCD_data PORTD
#define Data_dir_LCD_data DDRD
#define LCD_Control PORTB
#define Data_dir_LCD_Control DDRB
#define LCD_Enable 2
#define LCD_RW 1
#define LCD_RS 0
void USART_Initialization(void);
void peek_a_boo(void);
//void send_a_command(unsigned char command);
//void send_a_character(unsigned char Character);
//void Check_if_busy(void);
void send_a_string(char *name);
void ADC_Set_up(void);
void Start_conversion(void);
void PWM_Initialization(void);
int dutycycle=0;
void LCD_location(uint8_t x,uint8_t y);
char column_first_position[2]={0,64};
int main(void)
{
	
	//PWM_Initialization();
	USART_Initialization();
	ADC_Set_up();
	
	sei();
	Start_conversion();
	while (1)
	{
	}
}

void send_a_character(unsigned char Character)
{
  	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=Character;
	
	_delay_ms(100);
	
}

void send_a_string(char *name)
{
	while(*name>0)
	{
		send_a_character(*name ++);
	}
}
void ADC_Set_up()
{
	ADMUX|=(1<<REFS0)|(1<<MUX2)|(1<<MUX0)|(1<<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADPS2);
	DIDR0|=(1<<ADC5D);
}
void Start_conversion()
{
	ADCSRA|=(1<<ADSC);
}
/*void PWM_Initialization()
{
	TCCR1A|=(1<<COM1A1)|(1<<WGM10);
	TCCR1B|=(1<<WGM12)|(1<<CS10)|(1<<CS11);
	TIMSK1|=(1<<TOIE1);
}*/
ISR(ADC_vect)
{
	char ADC_Value[4];
	uint8_t thelow=(ADCL>>6);
	dutycycle=(ADCH<<2)|thelow;
	
	itoa(dutycycle,ADC_Value,10);
	send_a_string(ADC_Value);
	send_a_string(" ");
	Start_conversion();
}

void USART_Initialization()
{
	int UBRR_value=103;
	UBRR0H=(char)(UBRR_value>>8);
	UBRR0L=(char)(UBRR_value);
	UCSR0B|=(1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C|=(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
}
