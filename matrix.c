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

static void init_cols(void)
{
	// TODO
}

static matrix_row_t read_cols(void)
{
	// TODO
	return 1;
}

static void unselect_rows(void)
{
	// TODO
}

static void select_row(uint8_t row)
{
	// TODO
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
