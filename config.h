#define VENDOR_ID 0xF0DA
#define PRODUCT_ID 0x0666
#define DEVICE_VER 0x0001
#define MANUFACTURER vnc
#define PRODUCT S60-X
#define DESCRIPTION Custom keyboard firmware for Sentraq S60-X

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define DEBOUNCE 5

#define IS_COMMAND() ( \
	keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
