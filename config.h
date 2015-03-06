#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001
#define MANUFACTURER
#define PRODUCT
#define DESCRIPTION

#define MATRIX_ROWS
#define MATRIX_COLS

#define DEBOUNCE 5

#define IS_COMMAND() ( \
	keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
