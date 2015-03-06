#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001
#define MANUFACTURER p3lim
#define PRODUCT P60
#define DESCRIPTION Custom keyboard firmware

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define DEBOUNCE 5

#define IS_COMMAND() ( \
	keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
