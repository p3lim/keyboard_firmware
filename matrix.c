#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "util.h"

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

// col  0  1  2  3  4  5  6  7  8  9  10 11 12 13
// pin  F0 F1 F4 F5 F6 F7 B6 B5 B4 D7 D2 D3 C6 C7
static void init_cols(void)
{
	DDRF &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
	PORTF |= (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
	DDRB &= ~(1<<6 | 1<<5 | 1<<4);
	PORTB |= (1<<6 | 1<<5 | 1<<4);
	DDRD &= ~(1<<7 | 1<<3 | 1<<2);
	PORTD |= (1<<7 | 1<<3 | 1<<2);
	DDRC &= ~(1<<7 | 1<<6);
	PORTC |= (1<<7 | 1<<6);
}

static matrix_row_t read_cols(void)
{
	return (PINF&(1<<0) ? 0 : (1<<0)) |
		(PINF&(1<<1) ? 0 : (1<<1)) |
		(PINF&(1<<4) ? 0 : (1<<2)) |
		(PINF&(1<<5) ? 0 : (1<<3)) |
		(PINF&(1<<6) ? 0 : (1<<4)) |
		(PINF&(1<<7) ? 0 : (1<<5)) |
		(PINB&(1<<6) ? 0 : (1<<6)) |
		(PINB&(1<<5) ? 0 : (1<<7)) |
		(PINB&(1<<4) ? 0 : (1<<8)) |
		(PIND&(1<<7) ? 0 : (1<<9)) |
		(PIND&(1<<2) ? 0 : (1<<10)) |
		(PIND&(1<<3) ? 0 : (1<<11)) |
		(PINC&(1<<6) ? 0 : (1<<12)) |
		(PINC&(1<<7) ? 0 : (1<<13));
}

// row  0  1  2  3  4
// pin  B0 B1 B2 B3 B7
static void unselect_rows(void)
{
	DDRB &= ~0b10001111;
	PORTB &= ~0b10001111;
}

static void select_row(uint8_t row)
{
	switch(row){
		case 0:
			DDRB  |= (1<<0);
			PORTB &= ~(1<<0);
			break;
		case 1:
			DDRB  |= (1<<1);
			PORTB &= ~(1<<1);
			break;
		case 2:
			DDRB  |= (1<<2);
			PORTB &= ~(1<<2);
			break;
		case 3:
			DDRB  |= (1<<3);
			PORTB &= ~(1<<3);
			break;
		case 4:
			DDRB  |= (1<<7);
			PORTB &= ~(1<<7);
			break;
	}
}

void matrix_init(void)
{
	unselect_rows();
	init_cols();

	for(uint8_t row = 0; row < MATRIX_ROWS; row++){
		matrix[row] = 0;
		matrix_debouncing[row] = 0;
	}
}

uint8_t matrix_scan(void)
{
	for(uint8_t row = 0; row < MATRIX_ROWS; row++){
		select_row(row);
		_delay_us(30);

		matrix_row_t cols = read_cols();

		if(matrix_debouncing[row] != cols){
			matrix_debouncing[row] = cols;

			if(debouncing){
				debug("bounce!: ");
				debug_hex(debouncing);
				debug("\n");
			}

			debouncing = DEBOUNCE;
		}

		unselect_rows();
	}

	if(debouncing){
		if(--debouncing)
			_delay_ms(1);
		else {
			for(uint8_t row = 0; row < MATRIX_ROWS; row++)
				matrix[row] = matrix_debouncing[row];
		}
	}

	return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
	return matrix[row];
}

void matrix_print(void)
{
	print("\nr/c 0123456789ABCDEF\n");

	for(uint8_t row = 0; row < MATRIX_ROWS; row++){
		phex(row);
		print(": ");
		pbin_reverse16(matrix_get_row(row));
		print("\n");
	}
}

// have to specify this, for some reason it's not optional
void led_set(uint8_t usb_led){}
