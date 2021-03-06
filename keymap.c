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
		FN0,  LALT, LGUI,             SPC,                    FN1,  RGUI, RALT, RCTL),

	// Layer 1: Functions
	KEYMAP(
		TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  FN12, \
		CAPS, HOME, UP,   END,  PGUP, INS,  PAUS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, LEFT, DOWN, RGHT, PGDN, PSCR, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, VOLD, MUTE, VOLU, F21,  F22,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, TRNS, TRNS,             TRNS,                   TRNS, TRNS, TRNS, NO),

	// Layer 2: Functions
	KEYMAP(
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN22, TRNS, FN13, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN21, FN20, TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, F17,  F18,  F19,  TRNS, TRNS, \
		NO,   TRNS, TRNS,             TRNS,                   TRNS, TRNS, APP,  TRNS),
};

const action_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(1),
	[1] = ACTION_LAYER_MOMENTARY(2),
	[10] = ACTION_FUNCTION(0), // see action_function below
	[12] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_ESC),
	[13] = ACTION_MODS_KEY(MOD_RALT, KC_ENT),
	[20] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_QUOT),
	[21] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_SCLN),
	[22] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_LBRC)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	void (*key_method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
	uint8_t is_shift_down = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

	if(layer_state == 0)
		key_method(is_shift_down ? KC_GRAVE : KC_ESCAPE);
	else
		key_method(is_shift_down ? KC_ESCAPE : KC_GRAVE);

	send_keyboard_report();
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
