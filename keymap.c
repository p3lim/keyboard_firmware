#include <stdint.h>
#include <stdbool.h>
#include "action_code.h"
#include "bootloader.h"
#include "command.h"
#include "keycode.h"
#include "print.h"
#include "report.h"
#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Layer 0
	KEYMAP(
		ESC,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  BSPC, \
		TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, ENT, \
		LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, BSLS, \
		LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT, DEL, \
		FN1,  LGUI, LALT,             SPC,                    FN1,  RGUI, RALT, RCTL),

	// Layer 1: Functions
	KEYMAP(
		GRV,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  TRNS, \
		CAPS, HOME, UP,   END,  PGUP, INS,  PAUS, TRNS, P7,   P8,   P9,   TRNS, TRNS, TRNS, \
		TRNS, LEFT, DOWN, RGHT, PGDN, PSCR, TRNS, TRNS, P4,   P5,   P6,   TRNS, TRNS, \
		TRNS, VOLD, MUTE, VOLU, TRNS, TRNS, TRNS, TRNS, P1,   P2,   P3,   TRNS, TRNS, \
		TRNS, TRNS, TRNS,             TRNS,                   P0,   TRNS, TRNS, NO)
};

const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_MOMENTARY(1)
};

bool command_extra(uint8_t code)
{
	if(code == KC_B){
		clear_keyboard();
		print("\n\nJump to bootloader... ");
		_delay_ms(1000);
		bootloader_jump();
		print("failed.\n");
	}

	return false;
}
