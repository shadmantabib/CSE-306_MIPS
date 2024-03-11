#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>

// generated based on our provided serial
// like 1 is sw and .....


#define add 0x04
#define addi 0x07
#define sub 0x0D
#define subi 0x08
#define and 0x06
#define andi 0x0B
#define or 0x0F
#define ori 0x03
#define sll 0x00
#define srl 0x0E
#define nor 0x05
#define lw 0x0A
#define sw 0x09
#define beq 0x02
#define bneq 0x01
#define j 0x0C


// defining our operations for producing ALUOP and selectors for each and every mux . ALUOP is not needed actually . This part is done in our circuit

unsigned char memArr[32];
int controlMem[16] = {0xb04,0x280,
	0x240,0x504,
	0x006,0x806,
	0x606,0x104,
	0x304,0x110,
	0x12c,0x704,
	0x001,0x206,
0xd04,0x406};

int main(void)
{
	// To use PC2,3,4,5 pins for general I/O operations, JTAG must be disabled.(Enable JTD twice)
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	
	
	DDRA=0xFF; //output
	DDRB=0X00; //input
	DDRD=0X00; //input
	DDRC=0XFF; //output

	//DDRA=0X00; // ShowAddr A0 to A4; A5-> showaddrflag
	
	// opc BL
	// mRrWrDj AL
	// bNbEm2RmW AH
	// aluOPaluSRC CL


	PORTA = 0b11111111; // jump to bneq
	PORTB = 0b00000000;
	PORTD = 0b00000000;
	PORTC = 0b11111111; // alusrc and aluop



	while (1)
	{
		unsigned int operation = PINB & 0b00001111;
		// taking input opcode and configuring it to lower 4 bits 

		int ctrlOUT1 = controlMem[operation]%256;
		// in ctrlOUT1 is 32 bit. so it has total 12 bits that we need from lower side
		
		PORTA = ctrlOUT1 & 0b11111111;
		// getting lower 8 bits (jump(LSB) to bneq(MSB))

		ctrlOUT1 = controlMem[operation]/256;
		//discard the lower 8 bits so we getting ALUsrc(LSB) and ALUOP (reversed)
		
		PORTC = (ctrlOUT1 & 0b00001111)|( (operation<<4) & 0b11110000);
		//port C lower 4 bits getting the direct ctrlOUT1 higher 4 bits are opcode 

		// combining PORTA and PORTC = control unit

		_delay_ms(10);
	}
}
//Control