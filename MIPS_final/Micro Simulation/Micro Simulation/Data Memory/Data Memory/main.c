#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

unsigned char memArr[16];

int main(void)
{
	// To use PC2,3,4,5 pins for general I/O operations, JTAG must be disabled.(Enable JTD twice)
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0XFF; //output
	DDRB=0x00; //input
	DDRC=0x00; //input
	DDRD=0x0F; //lower output
	
	int currclk = 0;
	int prevclk = 0;
	int memread; //from pin D
	int memwrite; //from pin D
	int writedata;
	unsigned int addr;
	unsigned int dataout;
	unsigned int b;
	unsigned int d;
	
	for(int i=0; i<16; i++){
		memArr[i]=13;
	}
	
	while (1)
	{
		b = PINB ;
		writedata = b>>4; //upper 4 bits are what we are gonna write
		addr = b%16; // lower 4 bits are address
		d = PIND; //upper 4 bits clk,memread,memwrite
		prevclk = currclk;
		currclk = (d & 0b01000000)>>6;
		memread = (d & 0b00100000)>>5;
		memwrite= (d & 0b00010000)>>4;
		
		dataout = memArr[addr];
		
		//if(mem2reg==1) PORTA = dataout;
		//else PORTA = addr;
		
		PORTD = (dataout & 0b00001111);
		
		if(prevclk==0 && currclk==1 && memwrite==1){
			memArr[addr] = writedata;
		}
		_delay_ms(10);
		
		
	}
}

//Data Memory