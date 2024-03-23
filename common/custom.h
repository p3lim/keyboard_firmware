#pragma once

#include QMK_KEYBOARD_H

// requires altgr-intl keymap ("English (intl., with AltGr dead keys" in Gnome)
#define C_NO1 RALT(KC_Z) // æ
#define C_NO2 RALT(KC_L) // ø
#define C_NO3 RALT(KC_W) // å

enum {
    C_ESC0 = SAFE_RANGE, // layer 0 esc
    C_ESC1,              // layer 1 esc
    C_SPAM,
    C_PSCR
};
