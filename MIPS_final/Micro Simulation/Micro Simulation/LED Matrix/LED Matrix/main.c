#include <avr/io.h>
#include <util/delay.h>
#define INPUTPORT PORTA
#define OUTPUTPORT PORTB

char pins[] = {1, 2, 4, 8, 16, 32, 64, 128};
char vals[][8] = {0x00,0x70,0x48,0x48,0x70,0x40,0x40,0x00};

void up()
{
	while (1)
	{
		// Circular upward shift the character representation
		for (int shift = 0; shift < 8; shift++)
		{
			for (int i = 0; i < 8; i++)
			{
				INPUTPORT = pins[i];
				OUTPUTPORT = ~(vals[0][(i + shift) % 8]);
				_delay_ms(5);
			}
			_delay_ms(15);
			
		}
	}

}
void down()
{
	while (1)
	{
		// Circular downward shift the character representation
		for (int shift = 0; shift < 8; shift++)
		{
			for (int i = 0; i < 8; i++)
			{
				INPUTPORT = pins[i];
				OUTPUTPORT = ~(vals[0][(i - shift + 8) % 8]);
				_delay_ms(5);  // Adjust the delay as needed for desired speed
			}
			_delay_ms(15);
			
		}
	}
}
void left()
{
	while (1)
	{
		// Left shift the character representation
		for (int shift = 0; shift < 7; shift++)
		{
			for (int i = 0; i < 8; i++)
			{
				INPUTPORT = pins[i];
				OUTPUTPORT = ~(vals[0][i] << shift | vals[0][i] >> (8 - shift));
				_delay_ms(5);  // Adjust the delay as needed for desired speed
			}
			_delay_ms(15);
		}
	}
}
void right()
{
	while (1)
	{
		// Circular right shift the character representation
		for (int shift = 0; shift < 8; shift++)
		{
			for (int i = 0; i < 8; i++)
			{
				INPUTPORT = pins[i];
				OUTPUTPORT = ~(vals[0][i] >> shift | vals[0][i] << (8 - shift));
				_delay_ms(5);  // Adjust the delay as needed for desired speed
			}
			_delay_ms(15);
			
		}
	}
}

void flashWithoutInterrupt()
{
	while (1)
	{
		int i = 0;
		while (i < 8)  // Iterate through the columns
		{
			INPUTPORT = pins[i];
			OUTPUTPORT = ~vals[0][i];
			i++;
			_delay_ms(5);
		}

		INPUTPORT = 0x00;
		OUTPUTPORT = 0x00;
		_delay_ms(2000);
	}
}
int main(void)
{
	DDRA = 0xFF;  // Set PORTA as output
	DDRB = 0xFF;  // Set PORTD as output
	up();
	
	return 0;
}
