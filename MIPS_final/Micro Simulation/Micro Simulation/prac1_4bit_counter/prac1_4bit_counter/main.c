/*
 * prac1_4bit_counter.c
 *
 * Created: 1/14/2024 1:26:42 PM
 * Author : Tasriad Ahmed Tias
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#define dec 4
#define inc 4

int main(void)
{
    /* Replace with your application code */
	DDRA = 0b00001111;
	DDRB = 0b00000000;
	unsigned char count = 0;
	PORTA = 0;
    while (1) 
    {
		unsigned char in = PINB;
		if(in & 0b00000001)
		{
			_delay_ms(1000);
			count = (count + inc)%16;
			PORTA = count;
			while(in & 0b00000001);
		}		
		else if(in & 0b00000010)
		{
			_delay_ms(1000);
			count = (count - dec);
			if(count < 0)
			{
				count = count + 16;
			}
			PORTA = count;
			while(in & 0b00000010);
		}
    }
}

