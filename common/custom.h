#pragma once

#include QMK_KEYBOARD_H

enum {
    C_ESC0 = SAFE_RANGE, // layer 0 esc
    C_ESC1,              // layer 1 esc
    C_NO1,               // æ, requires RCTL to be a compose key in software
    C_NO2,               // ø, requires RCTL to be a compose key in software
    C_NO3,               // å, requires RCTL to be a compose key in software
    C_SPAM
};
