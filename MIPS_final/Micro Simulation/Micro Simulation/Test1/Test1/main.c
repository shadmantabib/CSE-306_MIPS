/*
 * Test1.c
 *
 * Created: 2/3/2024 10:09:42 AM
 * Author : Tasriad Ahmed Tias
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define F_CPU 1000000UL  // Set the clock frequency (1 MHz for example, adjust as needed)
#include <util/delay.h>

uint16_t value = 7;
uint16_t output;

void write_to_flash(uint16_t *address, uint16_t data) {
    cli(); // Disable interrupts during flash write
    eeprom_busy_wait();
    eeprom_write_word(address, data);
    sei(); // Enable interrupts after flash write
}

void init_LED() {
    // Initialize LED pin as output
    DDRB = 0xFF;  // Assuming you are using PORTB as output
	PORTB = 0x00;
}

int main(void)
{
    init_LED();  // Initialize LED pin
	_delay_ms(2000);
    // Set up EEPROM emulation (internal Flash write)
    write_to_flash((uint16_t*)0, value);

    // Read from EEPROM (internal Flash read)
    eeprom_busy_wait();
    output = eeprom_read_word((uint16_t*)0);
	PORTB = output;
    while (1) {
		;
    }
}
