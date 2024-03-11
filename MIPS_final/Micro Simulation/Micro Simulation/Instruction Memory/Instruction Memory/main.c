#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

unsigned int instructions[256]={
	0x7223,0x7334,0x4234,0xd424,0x7441,0x6434,0x5234,0xf234,0xb222,0x333f,0x8335,0x1321,0x7331,0x355f,0x9153,0xa133,
	0x8335,0xc130,0x8331,0x355f,0xb55d,0x0552,0xe552,0xb220,0xb330,0x3227,0x3337,0x2321,0x7221,0x355f,0x7222,0x7333,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};


int main(void)
{
	DDRA=0XFF; //output
	DDRB=0x00; //input
	DDRC=0xFF; //output
	DDRD = 0xFF; //output
	
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	unsigned int cur_instruction;
	unsigned int dst;
	unsigned int src_reg_2;
	unsigned int src_reg_1;
	unsigned int opcode;
	
	int pc = 0;
	PORTA = 0;
	PORTC = 0;
	
	/* Replace with your application code */
	while (1) {
		pc = PINB;
		cur_instruction = instructions[pc];
		dst = 0x000F & cur_instruction;
		src_reg_2 = 0x00F0 & cur_instruction;
		src_reg_1 = (0x0F00 & cur_instruction);
		opcode = (0xF000 & cur_instruction);
		PORTA = src_reg_2 | dst; //src2|dst
		PORTC = (src_reg_1 >> 8) | (opcode >> 8); // opcode|src1
		PORTD = (src_reg_1 >> 4) | (src_reg_2 >> 4); // src1 | src2
		// target address is PORTA full 8 bit
		_delay_ms(10);
	}
}
//InstructionMemory