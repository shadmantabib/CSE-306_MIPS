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

unsigned char memArr[32];

int main(void)
{
// To use PC2,3,4,5 pins for general I/O operations, JTAG must be disabled.(Enable JTD twice)
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0XFF; //output and zero flag
	DDRB=0x00; //input src1 and src2/destination
	DDRC=0x00; //input from control (ALUsrc(LSB),beq_flag,bneq_flag(3rd bit))
	DDRD=0x00; //input opcode(lower 4 bits) and destination/shift (higher 4 bits)

	//DDRA=0X00; // ShowAddr A0 to A4; A5-> showaddrflag
	
	// reg1 BL
	// reg2 DL
	// opc BH
	// out CL
	// zero A0


	PORTA = 0b00000001;
	PORTB = 0b11111111;
	PORTD = 0b00001111; 
	PORTC = 0b00000000;

	int reg1; //input A
	int reg2; //input B
	int operation; //opcode 
	int dataOutputReg = 0x00;
	int zeroFlag = 0; //output
	int beqf; //flag
	int bneqf; // flag from control unit

	while (1)
	{
		operation = PIND%16; //lower 4 bits in
		// for any immediate operations,shift type , any operation that has ALUsrc = 1 we use input from portD (higher bits)
		
		reg1 = PINB%16; //src1 or whom we shift
		reg2 =  (PINB >> 4); //src2/shift amount
		
		int c = PINC;  //pinc will take input ALUsrc(LSB),beq_flag,bneq_flag(3rd bit)
		beqf = (c & 0b0001);
		bneqf = (c & 0b0010)>>1;
		

		if (operation == add || operation ==addi || operation == lw || operation == sw)
		{
			dataOutputReg = (reg1 + reg2)%16;
		}
		else if (operation == sub || operation == subi || operation == beq || operation == bneq)
		{
			dataOutputReg = (reg1 - reg2 +16 )%16;
			
		}
		else if (operation == and || operation == andi)
		{
			dataOutputReg = reg1 & reg2;
		}
		else if (operation == or || operation == ori)
		{
			dataOutputReg = reg1 | reg2;
		}
		else if (operation == nor)
		{
			dataOutputReg = reg1 | reg2;
			dataOutputReg = (dataOutputReg ^ 15);
		}
		else if (operation == sll)
		{
			dataOutputReg = reg1 << reg2;
			dataOutputReg%=16;
		}
		else if (operation == srl)
		{
			dataOutputReg = reg1 >> reg2;
		}
		else if (operation == j)
		{
			dataOutputReg = 0;
		}

		if (dataOutputReg%16 == 0)
		{
			zeroFlag = 1;
		}
		else
		{
			zeroFlag = 0;
		}
		
		zeroFlag = (zeroFlag&beqf)|((!zeroFlag)&bneqf); // if 1 -> jump
		
		/*PORTC = 0x00;*/
		PORTA = dataOutputReg | (zeroFlag<<4);  // lower 4 bits are output and 5th bit is zero flag which determines if we jump
		//PORTC = 0xFF;
		
		
		
		_delay_ms(10);
	}
}