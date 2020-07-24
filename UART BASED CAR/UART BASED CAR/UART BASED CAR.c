
/*
 * uart.c
 *
 * Created: 10-01-2019 15:04:22
 *  Author: DURGESH
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd4bit.h"

void uart_string(unsigned char* str)
{
	int i;
	while(str[i]!='\0')
	{
		uart_send(str[i]);
		i++;
	}
}

void uart_init()
{
		UBRRL=51;    // set speed
		UCSRC|=(1<<URSEL)|(1<UCSZ0)|(1<<UCSZ1);  // select character size or UCSZ0,UCSZ1 &UCSZ2 decide for character size
		UCSRB|=(1<<TXEN)|(1<<RXEN);   // enable transmission
}
void uart_send(unsigned char rec)
{
	while(!(UCSRA&(1<<UDRE)));   //wait for transmission complete
	UDR=rec;	
}
unsigned char uart_rec()
{  
	while(!(UCSRA&(1<<RXC)));  //wait for receive data complete
	return UDR;                 //receive data form UDR
}
void uart_tx()
{
	UDR='G';
}



void main(void)
{ 
	
	DDRA=0xff;    //for output
	PORTC=0x00;
	DDRC=0xff;
	
	uart_init();
	lcd_init();
	lcd_string(" **WELCOME** ");
	_delay_ms(2000);
	lcd_cmd(0x01);
	while(1)
	{
		char a;
		a=uart_rec();
		if (a=='B')   // press B key for BACKWARD movement of motor in direction
		{
			PORTA=0x05;
				_delay_ms(50);
				lcd_cmd(0x01);
			lcd_string("BACKWARD");
		}
		else if (a=='F')  // press F key for movement of motor in FORWARD direction
		{
			PORTA=0x0A;
			
			lcd_cmd(0x01);
			lcd_string("FORWARD");
		}
		else if (a=='R')  // press R key for movement of motor in RIGHT direction
		{
			PORTA=0x09;
					
			lcd_cmd(0x01);
			lcd_string("RIGHT");
		}
		else if (a=='L')  // press L key for movement of motor in LEFT direction
		{
			PORTA=0x06;					
			lcd_cmd(0x01);
			lcd_string("LEFT");
		}
		else if (a=='S')  // press S key for Stop motor 
		{
			PORTA=0x00;												
			lcd_cmd(0x01);
			lcd_string("STOP");
		}
								
	}							
}