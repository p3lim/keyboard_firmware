#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "action_util.h"
#include "bootloader.h"
#include "command.h"
#include "keycode.h"
#include "print.h"
#include "report.h"
#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Layer 0
	KEYMAP(
		FN3,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  BSPC, \
		TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, ENT, \
		LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, BSLS, \
		LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT, DEL, \
		FN1,  LGUI, LALT,             SPC,                    FN2,  RGUI, RALT, FN0),

	// Layer 1: Functions
	KEYMAP(
		FN3,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  TRNS, \
		CAPS, HOME, UP,   END,  PGUP, INS,  PAUS, TRNS, P7,   P8,   P9,   TRNS, TRNS, TRNS, \
		TRNS, LEFT, DOWN, RGHT, PGDN, PSCR, TRNS, TRNS, P4,   P5,   P6,   TRNS, TRNS, \
		TRNS, VOLD, MUTE, VOLU, TRNS, TRNS, TRNS, TRNS, P1,   P2,   P3,   TRNS, TRNS, \
		TRNS, TRNS, TRNS,             TRNS,                   P0,   TRNS, TRNS, NO),

	// Layer 2: Functions
	KEYMAP(
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, APP, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP, HOME, UP,   END,  TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGDN, LEFT, DOWN, RGHT, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		NO,   TRNS, TRNS,             TRNS,                   TRNS, TRNS, TRNS, TRNS)
};

enum function_id {
	ESCAPE
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_F20),
	[1] = ACTION_LAYER_MOMENTARY(1),
	[2] = ACTION_LAYER_MOMENTARY(2),
	[3] = ACTION_FUNCTION(ESCAPE)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	if(id == ESCAPE){
		void (*method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
		uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

		if(layer_state == 0)
			method(shifted ? KC_GRAVE : KC_ESCAPE);
		else
			method(shifted ? KC_ESCAPE : KC_GRAVE);

		send_keyboard_report();
	}
}

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
