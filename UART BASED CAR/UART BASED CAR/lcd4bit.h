/*
 * lcd4bit.h
 *
 * Created: 07-01-2019 15:33:20
 *  Author: DELL
 */ 


#ifndef LCD4BIT_H_
#define LCD4BIT_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define RS PC0
#define RW PC1
#define EN PC2
#define DL5 _delay_ms(5)

void lcd_init()
{
	lcd_cmd(0x02);  //
	lcd_cmd(0x28);
	lcd_cmd(0x0e);
	
}
void lcd_cmd(unsigned char cmd)
{
	
	PORTC=(cmd)&(0xf0);      // select 8 bit mode lcd select
	PORTC &= ~((1<<RS)|(1<<RW)) ; //RS=0 & RW=0 for for select cmd register
	
	PORTC|=(1<<EN) ;   // EN=1
	DL5;
	PORTC&=~(1<<EN);     //EN =0
	DL5;
	
	PORTC=(cmd<<4)&(0xf0);      // select 8 bit mode lcd select
	PORTC &= ~((1<<RS)|(1<<RW)) ; //RS=0 & RW=0 for for select cmd register
	
	PORTC|=(1<<EN) ;   // EN=1
	DL5;
	PORTC&=~(1<<EN);     //EN =0
	DL5;

}
void lcd_data(unsigned char data)
{
	PORTC=(data)&(0xf0);
	PORTC |= (1<<RS) ; //RS=1 for select cmd register
	PORTC &= ~(1<<RW);  //RW=0 for select write data
	PORTC |=(1<<EN);   // EN=1
	DL5;
	PORTC&=~(1<<EN);     //EN =0
	DL5;
	
	PORTC=(data<<4)&(0xf0);
	PORTC |= (1<<RS) ; //RS=1 for select cmd register
	PORTC &= ~(1<<RW);  //RW=0 for select write data
	PORTC |=(1<<EN);   // EN=1
	DL5;
	PORTC&=~(1<<EN);     //EN =0
	DL5;
}

void lcd_string(unsigned char *x)
{
	while(*x!='\0')
	{
		lcd_data(*x);
		x++;
	}
}




#endif /* LCD4BIT_H_ */