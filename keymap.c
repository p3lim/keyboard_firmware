#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "action_macro.h"
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
		FN10, 1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  BSPC, \
		TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, ENT, \
		LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, BSLS, \
		LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT, DEL, \
		FN0,  LGUI, LALT,             SPC,                    FN1,  RGUI, RALT, FN11),

	// Layer 1: Functions
	KEYMAP(
		TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  TRNS, \
		CAPS, HOME, UP,   END,  PGUP, INS,  PAUS, TRNS, TRNS, TRNS, TRNS, FN17, TRNS, TRNS, \
		TRNS, LEFT, DOWN, RGHT, PGDN, PSCR, TRNS, TRNS, TRNS, TRNS, FN15, FN16, TRNS, \
		TRNS, VOLD, MUTE, VOLU, F21,  F22,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, TRNS, TRNS,             TRNS,                   TRNS, TRNS, TRNS, NO),

	// Layer 2: Functions
	KEYMAP(
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN12, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP, HOME, UP,   END,  FN13, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGDN, LEFT, DOWN, RGHT, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, F17,  F18,  F19,  TRNS, TRNS, \
		NO,   TRNS, TRNS,             TRNS,                   TRNS, TRNS, APP,  TRNS),
};

enum function_id {
	ESCAPE
};

enum macro_id {
	NO1,
	NO2,
	NO3
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(1),
	[1] = ACTION_LAYER_MOMENTARY(2),
	[10] = ACTION_FUNCTION(ESCAPE),
	[11] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_F20),
	[12] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_ESC),
	[13] = ACTION_MODS_KEY(MOD_RALT, KC_ENT),
	[15] = ACTION_MACRO(NO1),
	[16] = ACTION_MACRO(NO2),
	[17] = ACTION_MACRO(NO3)
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

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

	if(id == NO1){
		return shifted ?
			(record->event.pressed ? MACRO(T(F20), T(SLSH), D(LSHIFT), T(O), U(LSHIFT), END) : MACRO_NONE) :
			(record->event.pressed ? MACRO(T(F20), T(SLSH), T(O), END) : MACRO_NONE);
	} else if(id == NO2){
		return shifted ?
			(record->event.pressed ? MACRO(T(F20), D(LSHIFT), T(A), T(E), U(LSHIFT), END) : MACRO_NONE) :
			(record->event.pressed ? MACRO(T(F20), T(A), T(E), END) : MACRO_NONE);
	} else if(id == NO3){
		return shifted ?
			(record->event.pressed ? MACRO(T(F20), T(O), D(LSHIFT), T(A), U(LSHIFT), END) : MACRO_NONE) :
			(record->event.pressed ? MACRO(T(F20), T(O), T(A), END) : MACRO_NONE);
	}

	return MACRO_NONE;
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
