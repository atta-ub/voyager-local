#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "xL0xx/ZPj7mz"
#define LAYER_STATE_8BIT

#define RGB_MATRIX_STARTUP_SPD 60

// All LEDs off after 5 minutes without a key press; the next key turns them
// back on (that key still types). 2026-11-06, Voyager first.
#define RGB_MATRIX_TIMEOUT 300000  // ms

// Home row mod held + another key pressed and released inside the hold = mod,
// so a quick Ctrl (T or N) + Backspace (right thumb) is Ctrl+Backspace, not "t" + Backspace.
#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// Misfire guards, matching the laptop's kanata setup (notes/system/keyboard-remapping.org):
// 200 ms hold, 250 ms on pinky/ring (keymap.c); a same-hand key while holding = tap;
// a home row key within 150 ms of the previous letter or Space = tap.
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 150

// Caps Word also turns on by holding both Shifts (R and I) together until both
// count as held (~250 ms), then letting go. 2026-11-06.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Dynamic macros: room for 256 key events (about 128 keystrokes), shared by the
// two macros (default 128). 2026-11-07.
#define DYNAMIC_MACRO_SIZE 256
