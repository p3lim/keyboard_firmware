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

// col  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14
// pin  D0 D1 D2 D3 D5 D4 D6 D7 B4 B5 B6 C6 C7 E6 F1
static void init_cols(void)
{
	DDRF &= ~(1<<5);
	PORTF |= (1<<1);
	DDRE &= ~(1<<6);
	PORTE |= (1<<6);
	DDRD &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
	PORTD |= (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
	DDRC &= ~(1<<7 | 1<<6);
	PORTC |= (1<<7 | 1<<6);
	DDRB &= ~(1<<6 | 1<<5 | 1<<4);
	PORTB |= (1<<6 | 1<<5 | 1<<4);
}

static matrix_row_t read_cols(void)
{
	return
		(PIND&(1<<0) ? 0 : (1<<0)) |
		(PIND&(1<<1) ? 0 : (1<<1)) |
		(PIND&(1<<2) ? 0 : (1<<2)) |
		(PIND&(1<<3) ? 0 : (1<<3)) |
		(PIND&(1<<5) ? 0 : (1<<4)) |
		(PIND&(1<<4) ? 0 : (1<<5)) |
		(PIND&(1<<6) ? 0 : (1<<6)) |
		(PIND&(1<<7) ? 0 : (1<<7)) |
		(PINB&(1<<4) ? 0 : (1<<8)) |
		(PINB&(1<<5) ? 0 : (1<<9)) |
		(PINB&(1<<6) ? 0 : (1<<10)) |
		(PINC&(1<<6) ? 0 : (1<<11)) |
		(PINC&(1<<7) ? 0 : (1<<12)) |
		(PINE&(1<<6) ? 0 : (1<<13)) |
		(PINF&(1<<1) ? 0 : (1<<14));
}

// row  0  1  2  3  4
// pin  B7 B3 B2 B1 B0
static void unselect_rows(void)
{
	DDRB &= ~0b10001111;
	PORTB &= ~0b10001111;
}

static void select_row(uint8_t row)
{
	switch(row){
		case 0:
			DDRB  |= (1<<7);
			PORTB &= ~(1<<7);
			break;
		case 1:
			DDRB  |= (1<<3);
			PORTB &= ~(1<<3);
			break;
		case 2:
			DDRB  |= (1<<2);
			PORTB &= ~(1<<2);
			break;
		case 3:
			DDRB  |= (1<<1);
			PORTB &= ~(1<<1);
			break;
		case 4:
			DDRB  |= (1<<0);
			PORTB &= ~(1<<0);
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

bool matrix_is_modified(void)
{
	if(debouncing)
		return false;
	return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
	return (matrix[row] & ((matrix_row_t)1<<col));
}

uint8_t matrix_key_count(void)
{
	uint8_t count = 0;
	for(uint8_t row = 0; row < MATRIX_ROWS; row++)
		count += bitpop16(matrix[row]);
	return count;
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
