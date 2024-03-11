/*
 * GccApplication1.c
 *
 * Created: 2/8/2024 2:40:37 PM
 * Author : DELL
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#define bselect_mask 0b00100000
#define isjump_mask 0b00010000
#define dst_mask 0b00001111
#define clock_mask 0b10000000


int main(void)
{
    /* Replace with your application code */
  DDRA = 0xFF; //for pc output
  DDRB = 0x00; // jump address
  DDRD = 0x00; // clock(7th bit) bselect(5th bit) isjump(4th bit) dst(0-3bit)
  PORTB = 0x00;
  PORTD = 0x00;
  PORTA = 0x00;
  unsigned int pc = 0;
  unsigned int curr_clock = 0;
  unsigned int prev_clock = 0;
  unsigned int bselect = 0;
  unsigned int isjump = 0;
  unsigned int dst =0;
  unsigned int jump_address = 0;
  
    while (1) 
    {
    jump_address = PINB;
    prev_clock = curr_clock;
    curr_clock= (PIND & clock_mask) >> 7;
    bselect = (PIND & bselect_mask) >> 5;
    isjump = (PIND & isjump_mask) >>4 ;
    dst = (PIND & dst_mask);
    if(prev_clock == 1 && curr_clock == 0)
    {
      if(isjump)
      {
        pc = jump_address;
      }
      else if(bselect)
      {
        pc =pc + 1 + dst;
      }
      else{
        pc = pc + 1;
      }
      PORTA = pc;
    }
    _delay_ms(10);
    
    }
}
//PC