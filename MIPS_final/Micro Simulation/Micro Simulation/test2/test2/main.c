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

void write_hex_data_to_flash(const uint16_t *hex_data, uint16_t length) {
    for (uint16_t i = 0; i < length; ++i) {
        write_to_flash((uint16_t*)(i * sizeof(uint16_t)), hex_data[i]);
        _delay_ms(10);  // Delay for stability in writing to Flash (adjust as needed)
    }
}

int main(void)
{
    init_LED();  // Initialize LED pin

    // Example hex data (replace with your own data)
    uint16_t hex_data[] = {0x0001, 0x004, 0x0002, 0x0007};
    uint16_t data_length = sizeof(hex_data) / sizeof(hex_data[0]);
	uint16_t output;
	PORTB =0x00;
    _delay_ms(2000);

    // Write hex data to internal Flash memory
    write_hex_data_to_flash(hex_data, data_length);
	eeprom_busy_wait();
	output = eeprom_read_word((uint16_t*)(1 * sizeof(uint16_t)));
	PORTB = output;
    while (1) {
        // Your main loop code here
        ;
    }
}
