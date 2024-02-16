#include "custom.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
    * ,-----------------------------------------------------------------------------------------.
    * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
    * |-----------------------------------------------------------------------------------------+
    * |   Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |        |
    * |---------------------------------------------------------------------------------| Enter |
    * |   Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |  \  |       |
    * |-----------------------------------------------------------------------------------------+
    * |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   Shift   | Del |
    * |-----------------------------------------------------------------------------------------+
    * |  FN1  | Alt |  GUI   |              Space                |  FN2   | GUI | Alt |  Ctrl   |
    * `-----------------------------------------------------------------------------------------'
    */
    [0] = LAYOUT(
        C_ESC0,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DEL,
        MO(1),   KC_LGUI, KC_LALT,                   KC_SPC,                             MO(2),   KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* FN1
    * ,-----------------------------------------------------------------------------------------.
    * |  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |           |
    * |-----------------------------------------------------------------------------------------+
    * |  Caps  | Home| Up  | End | PgUp|     |     |     |     |     |     |     |     |        |
    * |---------------------------------------------------------------------------------|       |
    * |         | Left| Down|Right| PgDn|PrtSc|     |     |     |     |     |     |     |       |
    * |-----------------------------------------------------------------------------------------+
    * |           | VolU| Mute| VolD|     |     |     |     |     |     |     |           |     |
    * |-----------------------------------------------------------------------------------------+
    * |       |     |        |                                   |        |     |     |         |
    * `-----------------------------------------------------------------------------------------'
    */
    [1] = LAYOUT(
        C_ESC1,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        KC_CAPS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_PSCR, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            KC_NO,   _______, _______, _______
    ),

    /* FN2
    * ,-----------------------------------------------------------------------------------------.
    * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
    * |-----------------------------------------------------------------------------------------+
    * |        |     |     |     |     |     |     |     |     |     |     |  Å  |     |        |
    * |---------------------------------------------------------------------------------|       |
    * |         |     |     |     |     |     |     |     |     |     |  Ø  |  Æ  |     |       |
    * |-----------------------------------------------------------------------------------------+
    * |           |     |     |     |     |     |     |     |     |     |     |           |     |
    * |-----------------------------------------------------------------------------------------+
    * |       |     |        |                                   |        |     |     |         |
    * `-----------------------------------------------------------------------------------------'
    */
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO3,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_NO2,   C_NO1,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_NO,   _______, _______,                   C_SPAM,                             _______, _______, _______, _______
    ),
};
