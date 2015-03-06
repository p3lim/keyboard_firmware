#include <stdint.h>
#include <avr/pgmspace.h>
#include "action_code.h"
#include "keyboard.h"
#include "keycode.h"
#include "keymap.h"

void led_set(uint8_t usb_led){}

uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

action_t keymap_fn_to_action(uint8_t keycode)
{
	return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
