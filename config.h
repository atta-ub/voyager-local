#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "xL0xx/ZPj7mz"
#define LAYER_STATE_8BIT

#define RGB_MATRIX_STARTUP_SPD 60

// Home row mod held + another key pressed and released inside the hold = mod,
// so a quick Ctrl (T or N) + Backspace is Ctrl+Backspace, not "t" + Backspace.
#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// Misfire guards, matching the laptop's kanata setup (notes/system/keyboard-remapping.org):
// 200 ms hold, 250 ms on pinky/ring (keymap.c); a same-hand key while holding = tap;
// a home row key within 150 ms of the previous letter or Space = tap.
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 150
