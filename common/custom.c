#include "custom.h"

// the userspace functions call "keymap" variants of themselves which are weak and can be overridden

static bool state_esc = false;
static bool state_spam = false;
static bool pscr_blocked = false;
static uint8_t pscr_code;

static uint16_t state_spam_timer = 0;
static uint16_t state_spam_interval = 25; // ms

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record){
    // this can be overridden in a keymap
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if(!process_record_keymap(keycode, record))
        return false;

    // add custom keycodes
    const uint8_t mods = get_mods();
    uint8_t shifted = mods & MOD_MASK_SHIFT;

    switch(keycode){
        case C_ESC0: // layer 0
            if(record->event.pressed){
                state_esc = shifted;
                register_code(shifted ? KC_GRAVE : KC_ESCAPE);
            } else {
                unregister_code(state_esc ? KC_GRAVE : KC_ESCAPE);
            }
            return false;
        case C_ESC1: // layer 1
            if(record->event.pressed){
                state_esc = shifted;
                register_code(shifted ? KC_ESCAPE : KC_GRAVE);
            } else {
                unregister_code(state_esc ? KC_ESCAPE : KC_GRAVE);
            }
            return false;
        case C_SPAM:
            state_spam = record->event.pressed;
            state_spam_timer = timer_read();
            return false;
        // custom handling for F3 on layer to work with minecraft
        case KC_F3:
            pscr_blocked = record->event.pressed;
            return true;
        case C_PSCR:
            if(record->event.pressed){
                if(pscr_blocked){
                    pscr_code = KC_G;
                } else {
                    pscr_code = KC_PSCR;
                }

                register_code(pscr_code);
            } else {
                unregister_code(pscr_code);
            }
            return false;
        default:
            return true;
    }
}

__attribute__ ((weak))
void matrix_scan_keymap(void){
    // this can be overridden in a keymap
}

void matrix_scan_user(void){
    matrix_scan_keymap();

    if(state_spam){
        if(timer_elapsed(state_spam_timer) > state_spam_interval){
            state_spam_timer = timer_read();

            tap_code(KC_SPACE);
        }
    }
}
