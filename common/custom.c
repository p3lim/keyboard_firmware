#include "custom.h"

// the userspace functions call "keymap" variants of themselves which are weak and can be overridden

static bool state_esc = false;

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
        case C_NO1: // æ
            if(record->event.pressed){
                // we use shift for A and E to capitalize, no need to handle this here
                tap_code(KC_RCTL);
                tap_code(KC_A);
                tap_code(KC_E);
            }
            return false;
        case C_NO2: // ø
            if(record->event.pressed){
                // the "/" symbol can't be shifted, so we have to deal with that
                if(shifted){
                    unregister_code(KC_LSFT); // reset shift state, I never use RSFT
                    tap_code(KC_RCTL);
                    tap_code(KC_SLSH);
                    tap_code16(S(KC_O)); // shifted
                    register_code(KC_LSFT); // restore shift state
                } else {
                    tap_code(KC_RCTL);
                    tap_code(KC_SLSH);
                    tap_code(KC_O);
                }
            }
            return false;
        case C_NO3: // å
            if(record->event.pressed){
                // the "o" character can't be shifted, so we have to deal with that
                if(shifted){
                    unregister_code(KC_LSFT); // reset shift state, I never use RSFT
                    tap_code(KC_RCTL);
                    tap_code(KC_O);
                    tap_code16(S(KC_A)); // shifted
                    register_code(KC_LSFT); // restore shift state
                } else {
                    tap_code(KC_RCTL);
                    tap_code(KC_O);
                    tap_code(KC_A);
                }
            }
            return false;
        default:
            return true;
    }
}
