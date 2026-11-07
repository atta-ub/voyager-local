#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

// LED keys (layer 2 top row): themes on 1-5, Bright and Dim toggles on 7 and 8.
// See the LED section below.
enum custom_keycodes {
  THEME_1 = ZSA_SAFE_RANGE,
  THEME_2,
  THEME_3,
  THEME_4,
  THEME_5,
  LED_BRIGHT,
  LED_DIM,
  DM_KEY1,  // dynamic macro 1: base top right, and layer 2 J position
  DM_KEY2,  // dynamic macro 2: layer 2 L position
};

// Lower thumbs (2026-11-06): hold = layer 1 (numbers) on both.
// Left tap = Repeat Key (repeats the last key; F24 is only a placeholder,
// see process_record_user). Right tap = Backspace (was Down/Up arrows);
// Shift + right tap = Delete.
#define REP_NUM  LT(1, KC_F24)
#define BSPC_NUM LT(1, KC_BSPC)

// Local keymap, started from Oryx layout xL0xx/ZPj7mz (2026-10-26).
// Layer 0: Colemak-DH base, 1: numbers and symbols (hold either lower thumb),
// 2: F-keys, arrows, Home/End/PgUp/PgDn, media, QK_BOOT top right (hold Space, as on the laptop);
//    top row: 1-5 = LED themes, 6 = all LEDs on/off, 7 = Bright, 8 = Dim.
// Enter: tap = Enter, hold = Meta (xmonad mod), next to Meta on G and M.
// Dynamic macros (2026-11-07): macro 1 = base top right and layer 2 J position,
// macro 2 = layer 2 L position (left of F11/F12). Hold = start recording,
// tap while recording = stop, tap = play. Caps Word is on both Shifts (R + I).
// Top-left key on every layer = Layer Lock (2026-11-06): hold a layer key, tap it
// to keep that layer on; tap it again to go back. Glows white while locked.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    QK_LLCK,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           DM_KEY1,
    KC_TAB,         KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,                                           KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCLN,        KC_DELETE,
    KC_ESCAPE,      KC_A,           MT(MOD_LSFT, KC_R),MT(MOD_LALT, KC_S),MT(MOD_LCTL, KC_T),MT(MOD_LGUI, KC_G),                                         MT(MOD_RGUI, KC_M),MT(MOD_RCTL, KC_N),MT(MOD_LALT, KC_E),MT(MOD_RSFT, KC_I),KC_O,           KC_QUOTE,
    KC_LEFT,        KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                           KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RIGHT,
                                                    LT(2, KC_SPACE),REP_NUM,                                 BSPC_NUM,   MT(MOD_RGUI, KC_ENTER)
  ),
  [1] = LAYOUT_voyager(
    QK_LLCK,        KC_NO,          KC_BSLS,        KC_EXLM,        KC_TILD,        KC_NO,                                          KC_NO,          KC_NO,          KC_COLN,        KC_PIPE,        KC_NO,          KC_NO,
    KC_MINUS,       KC_PLUS,        KC_LBRC,        KC_LCBR,        KC_LPRN,        KC_UNDS,                                        KC_MINUS,       KC_RPRN,        KC_RCBR,        KC_RBRC,        KC_SCLN,        KC_DQUO,
    KC_EQUAL,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_QUOTE,
    KC_PLUS,        KC_ASTR,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_CIRC,        KC_AMPR,        KC_COMMA,       KC_DOT,         KC_SLASH,       KC_GRAVE,
                                                    KC_SPACE,       KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_ENTER
  ),
  [2] = LAYOUT_voyager(
    QK_LLCK,        THEME_1,        THEME_2,        THEME_3,        THEME_4,        THEME_5,                                        RM_TOGG,        LED_BRIGHT,     LED_DIM,        KC_NO,          KC_NO,          QK_BOOT,
    KC_NO,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_NO,                                          DM_KEY1,        DM_KEY2,        KC_F11,         KC_F12,         KC_NO,          KC_NO,
    KC_NO,          KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_NO,
    KC_NO,          KC_HOME,        KC_PGDN,        KC_PAGE_UP,     KC_END,         KC_NO,                                          KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,
                                                    KC_TRANSPARENT, KC_NO,                                          KC_NO,          KC_NO
  ),
};

// Chordal Hold handedness. Outer columns (Esc, Tab, arrows, Del, ...) and
// thumbs are '*', so T + the Backspace thumb still gives Ctrl+Backspace and
// thumb layer keys never turn into taps.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_voyager(
  '*', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', '*',
                      '*', '*',      '*', '*'
);

// Pinky and ring mods (R I) need a longer hold.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MT(MOD_LSFT, KC_R):
    case MT(MOD_RSFT, KC_I):
      return TAPPING_TERM + 50;
  }
  return TAPPING_TERM;
}

// Space is time-only, like kanata on the laptop: a space-letter roll never
// turns into an F-key. Everything else uses permissive hold.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  return keycode != LT(2, KC_SPACE);
}


extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

// Dynamic macros, two slots, one key each: hold = record, tap = stop / play.
static uint8_t  dm_recording = 0;      // slot being recorded (1 or 2), 0 = none
static bool     dm_stopping  = false;  // this press stopped a recording
static uint16_t dm_timer     = 0;

bool dynamic_macro_record_start_user(int8_t direction) { dm_recording = direction > 0 ? 1 : 2; return true; }
bool dynamic_macro_record_end_user(int8_t direction)   { dm_recording = 0; return true; }

// Not recorded: the macro keys, Layer Lock, and layer-key holds (Space for
// layer 2, the number thumbs). Otherwise replaying could leave a layer stuck on.
// Taps of those thumbs (Space, Backspace, Repeat) are recorded as usual.
bool dynamic_macro_valid_key_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == DM_KEY1 || keycode == DM_KEY2 || keycode == QK_LLCK) return false;
  if (IS_QK_LAYER_TAP(keycode) && record->tap.count == 0) return false;
  return true;
}

// ---------------------------------------------------------------------------
// LEDs: themes and per-key colours (the same code on the Voyager and Moonlander).
// Colours are {hue, sat, val}, 0-255; val is scaled by the board brightness keys.
//
// Each key's role is found from the keymap at start-up, so colours follow keymap
// edits. In order of priority:
// - Unused: KC_NO on the current layer is off (or dim), so a held layer shows
//   only the keys that do something there.
// - Boot: QK_BOOT (flash mode).
// - Held mod: a mod-tap key that is pressed while its modifier is active.
// - Caps Word, base layer: letters and the Caps Word key while Caps Word is on.
// - Groups, layers 1 and 2: numbers, arrows, Home/End/PgUp/PgDn, F-keys, media.
// - Theme keys (layer 2): each shows its own theme's base colour.
// - Layer Lock key (top left): white while the current layer is locked.
// - Macro keys (top right; layer 2 J and L): red while their macro is recording.
// - Mod-tap, base layer: home-row mods and Enter/Meta.
// - Layer tap, base layer: Space, Down, Up show the colour of the layer they open.
// Everything else has the layer colour.
//
// Themes (2026-11-06): hold Space, then 1-5 picks a theme (kept after unplugging),
// 6 turns all LEDs on/off (RM_TOGG). Lights also go off after 5 minutes idle
// (RGB_MATRIX_TIMEOUT in config.h).
// Brightness modes (2026-11-06), kept after unplugging: 7 = Bright toggle (every
// colour below BRIGHT_VAL is raised to it; brighter ones, like the mods, stay),
// 8 = Dim toggle (everything at DIM_PERCENT). Turning one on turns the other off;
// the key of the active mode glows white.
enum led_kind {
  LED_NORMAL,  // layer colour
  LED_UNUSED, LED_BOOT, LED_MOD_HELD, LED_MOD_TAP,
  LED_NUMBER, LED_ARROW, LED_NAV, LED_FKEY, LED_MEDIA,
  LED_CAPS_WORD,
  LED_KIND_COUNT,
  LED_LAYER_TAP = LED_KIND_COUNT,  // colour = theme layer colour of the target layer
  LED_THEME,                       // colour = that theme's base colour
  LED_MODE_KEY,                    // Bright/Dim key: white while its mode is on
  LED_LOCK_KEY,                    // Layer Lock key: white while a layer is locked
  LED_MACRO_KEY,                   // macro key: red while its slot is recording
};

#define THEME_LAYERS 3
#define LAYER_TAP_VAL 230  // brightness of the layer-tap thumb keys and theme keys
#define BRIGHT_VAL    200  // Bright mode: minimum brightness of every lit colour
#define DIM_PERCENT    35  // Dim mode: brightness of every colour, in percent

typedef struct {
  uint8_t layer[THEME_LAYERS][3];
  uint8_t kind[LED_KIND_COUNT][3];
} led_theme_t;

static const led_theme_t PROGMEM themes[] = {
  // 1. Green + coral: green base, violet numbers layer, blue FN layer.
  {
    .layer = {{87, 245, 150}, {191, 227, 150}, {139, 184, 150}},
    .kind = {
      [LED_UNUSED]    = {  0,   0,   0},  // off
      [LED_BOOT]      = {  0, 255, 255},  // red
      [LED_MOD_HELD]  = {  0,   0, 255},  // white
      [LED_MOD_TAP]   = {  8, 255, 255},  // coral
      [LED_NUMBER]    = { 43, 255, 230},  // yellow
      [LED_ARROW]     = {  0,   0, 230},  // white
      [LED_NAV]       = {  0,   0, 230},  // white
      [LED_FKEY]      = { 43, 255, 230},  // yellow
      [LED_MEDIA]     = {223, 255, 230},  // pink
      [LED_CAPS_WORD] = {206, 255, 230},  // magenta
    },
  },
  // 2. Teal + coral: teal base, pink numbers layer, deep blue FN layer.
  {
    .layer = {{120, 255, 150}, {225, 200, 150}, {165, 255, 150}},
    .kind = {
      [LED_UNUSED]    = {  0,   0,   0},  // off
      [LED_BOOT]      = {  0, 255, 255},  // red
      [LED_MOD_HELD]  = {  0,   0, 255},  // white
      [LED_MOD_TAP]   = {  8, 255, 255},  // coral
      [LED_NUMBER]    = { 43, 255, 230},  // yellow
      [LED_ARROW]     = {  0,   0, 230},  // white
      [LED_NAV]       = {  0,   0, 230},  // white
      [LED_FKEY]      = { 43, 255, 230},  // yellow
      [LED_MEDIA]     = {128, 255, 230},  // cyan
      [LED_CAPS_WORD] = {206, 255, 230},  // magenta
    },
  },
  // 3. Las Vegas: neon purple base, gold mods, hot pink numbers layer,
  //    electric blue FN layer, cyan Caps Word.
  {
    .layer = {{196, 255, 150}, {235, 255, 150}, {160, 255, 150}},
    .kind = {
      [LED_UNUSED]    = {  0,   0,   0},  // off
      [LED_BOOT]      = {  0, 255, 255},  // red
      [LED_MOD_HELD]  = {  0,   0, 255},  // white
      [LED_MOD_TAP]   = { 32, 255, 255},  // gold
      [LED_NUMBER]    = { 32, 255, 230},  // gold
      [LED_ARROW]     = {  0,   0, 230},  // white
      [LED_NAV]       = {  0,   0, 230},  // white
      [LED_FKEY]      = { 32, 255, 230},  // gold
      [LED_MEDIA]     = {235, 255, 230},  // hot pink
      [LED_CAPS_WORD] = {128, 255, 230},  // neon cyan
    },
  },
  // 4. Classic: the original blue base, indigo numbers layer, green FN layer,
  //    amber mods.
  {
    .layer = {{139, 184, 150}, {164, 227, 150}, {87, 245, 150}},
    .kind = {
      [LED_UNUSED]    = {  0,   0,   0},  // off
      [LED_BOOT]      = {  0, 255, 255},  // red
      [LED_MOD_HELD]  = {  0,   0, 255},  // white
      [LED_MOD_TAP]   = { 21, 255, 255},  // amber
      [LED_NUMBER]    = { 43, 255, 230},  // yellow
      [LED_ARROW]     = {  0,   0, 230},  // white
      [LED_NAV]       = {  0,   0, 230},  // white
      [LED_FKEY]      = { 43, 255, 230},  // yellow
      [LED_MEDIA]     = {223, 255, 230},  // pink
      [LED_CAPS_WORD] = {206, 255, 230},  // magenta
    },
  },
  // 5. Dark (ef-themes style): backgrounds barely lit, accents bright.
  {
    .layer = {{139, 120, 25}, {191, 200, 30}, {87, 200, 30}},
    .kind = {
      [LED_UNUSED]    = {  0,   0,   0},  // off
      [LED_BOOT]      = {  0, 255, 200},  // red
      [LED_MOD_HELD]  = {  0,   0, 255},  // white
      [LED_MOD_TAP]   = {  8, 230, 200},  // coral
      [LED_NUMBER]    = { 43, 230, 180},  // yellow
      [LED_ARROW]     = {  0,   0, 160},  // soft white
      [LED_NAV]       = {  0,   0, 160},  // soft white
      [LED_FKEY]      = { 43, 230, 180},  // yellow
      [LED_MEDIA]     = {223, 230, 180},  // pink
      [LED_CAPS_WORD] = {206, 230, 200},  // magenta
    },
  },
};
#define THEME_COUNT (sizeof(themes) / sizeof(themes[0]))

enum led_mode { MODE_NORMAL, MODE_BRIGHT, MODE_DIM };

// Saved in the user EEPROM slot: bits 0-7 theme, bits 8-9 brightness mode.
static uint8_t current_theme = 0;
static uint8_t current_mode  = MODE_NORMAL;

static void save_led_settings(void) {
  eeconfig_update_user(current_theme | ((uint32_t)current_mode << 8));
}

static void set_theme(uint8_t theme) {
  current_theme = theme < THEME_COUNT ? theme : 0;
  save_led_settings();
}

static void toggle_mode(uint8_t mode) {
  current_mode = current_mode == mode ? MODE_NORMAL : mode;
  save_led_settings();
}

#define LAYER_COUNT (sizeof(keymaps) / sizeof(keymaps[0]))

static uint8_t led_kind[LAYER_COUNT][RGB_MATRIX_LED_COUNT];
static uint8_t led_arg[LAYER_COUNT][RGB_MATRIX_LED_COUNT];  // LT: target layer; theme key: theme
static uint8_t led_mods[RGB_MATRIX_LED_COUNT];  // 8-bit mods of a base-layer MT key, else 0
static keypos_t led_pos[RGB_MATRIX_LED_COUNT];
static bool led_caps_word[RGB_MATRIX_LED_COUNT];  // base-layer letter or CW_TOGG key

// MT stores 5-bit mods (bit 4 = right hand); get_mods() uses 8 bits.
static uint8_t mod_tap_mods8(uint16_t kc) {
  uint8_t m = QK_MOD_TAP_GET_MODS(kc);
  return (m & 0x10) ? (m & 0x0F) << 4 : m;
}

static uint8_t group_kind(uint16_t kc) {
  if (kc >= KC_1 && kc <= KC_0)                         return LED_NUMBER;
  if (kc >= KC_RIGHT && kc <= KC_UP)                    return LED_ARROW;
  if (kc == KC_HOME || kc == KC_END ||
      kc == KC_PAGE_UP || kc == KC_PAGE_DOWN)           return LED_NAV;
  if ((kc >= KC_F1 && kc <= KC_F12) ||
      (kc >= KC_F13 && kc <= KC_F24))                   return LED_FKEY;
  if (IS_CONSUMER_KEYCODE(kc))                          return LED_MEDIA;
  return LED_NORMAL;
}

static void find_led_kinds(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      uint8_t led = g_led_config.matrix_co[row][col];
      if (led == NO_LED) continue;
      keypos_t pos = {.row = row, .col = col};
      uint16_t base = keymap_key_to_keycode(0, pos);
      led_pos[led]  = pos;
      led_mods[led] = IS_QK_MOD_TAP(base) ? mod_tap_mods8(base) : 0;
      uint16_t tap  = IS_QK_MOD_TAP(base) ? QK_MOD_TAP_GET_TAP_KEYCODE(base) : base;
      led_caps_word[led] = (tap >= KC_A && tap <= KC_Z) || base == CW_TOGG;
      for (uint8_t layer = 0; layer < LAYER_COUNT; layer++) {
        uint16_t kc = keymap_key_to_keycode(layer, pos);
        uint8_t kind = LED_NORMAL, arg = 0;
        if (kc == KC_NO)                         kind = LED_UNUSED;
        else if (kc == QK_BOOT)                  kind = LED_BOOT;
        else if (kc >= THEME_1 && kc < THEME_1 + THEME_COUNT) {
          kind = LED_THEME;
          arg  = kc - THEME_1;
        }
        else if (kc == QK_LLCK)                  kind = LED_LOCK_KEY;
        else if (kc == DM_KEY1 || kc == DM_KEY2) {
          kind = LED_MACRO_KEY;
          arg  = kc == DM_KEY1 ? 1 : 2;
        }
        else if (kc == LED_BRIGHT || kc == LED_DIM) {
          kind = LED_MODE_KEY;
          arg  = kc == LED_BRIGHT ? MODE_BRIGHT : MODE_DIM;
        }
        else if (layer > 0)                      kind = group_kind(kc);
        else if (IS_QK_MOD_TAP(base))            kind = LED_MOD_TAP;
        else if (IS_QK_LAYER_TAP(base) &&
                 QK_LAYER_TAP_GET_LAYER(base) < THEME_LAYERS) {
          kind = LED_LAYER_TAP;
          arg  = QK_LAYER_TAP_GET_LAYER(base);
        }
        led_kind[layer][led] = kind;
        led_arg[layer][led]  = arg;
      }
    }
  }
}

static RGB theme_rgb(const uint8_t *c, int16_t val_override) {
  HSV hsv = {
    .h = pgm_read_byte(&c[0]),
    .s = pgm_read_byte(&c[1]),
    .v = val_override >= 0 ? val_override : pgm_read_byte(&c[2]),
  };
  if (hsv.v > 0) {  // off stays off
    if (current_mode == MODE_BRIGHT && hsv.v < BRIGHT_VAL) hsv.v = BRIGHT_VAL;
    if (current_mode == MODE_DIM) hsv.v = (uint16_t)hsv.v * DIM_PERCENT / 100;
  }
  return hsv_to_rgb_with_value(hsv);
}

static void set_layer_color(uint8_t layer) {
  const led_theme_t *t = &themes[current_theme];
  RGB bg = theme_rgb(t->layer[layer], -1);
  rgb_matrix_set_color_all(bg.r, bg.g, bg.b);

  RGB colors[LED_KIND_COUNT];
  for (uint8_t k = 0; k < LED_KIND_COUNT; k++) colors[k] = theme_rgb(t->kind[k], -1);

  uint8_t mods = get_mods();
  bool caps_word = layer == 0 && is_caps_word_on();
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    uint8_t kind = led_kind[layer][i];
    uint8_t arg  = led_arg[layer][i];
    if (caps_word && led_caps_word[i]) kind = LED_CAPS_WORD;
    if (kind != LED_UNUSED && kind != LED_BOOT && (mods & led_mods[i]) &&
        matrix_is_on(led_pos[i].row, led_pos[i].col)) {
      kind = LED_MOD_HELD;
    }
    RGB c;
    if (kind == LED_MACRO_KEY) {
      if (dm_recording != arg) continue;  // layer colour unless this slot records
      kind = LED_BOOT;              // red while recording
    }
    if (kind == LED_LOCK_KEY) {
      if (!is_layer_locked(layer)) continue;  // layer colour while unlocked
      kind = LED_MOD_HELD;                    // white while locked
    }
    if (kind == LED_MODE_KEY) {
      if (current_mode != arg) continue;  // layer colour while off
      kind = LED_MOD_HELD;                // white while on
    }
    if (kind == LED_NORMAL) continue;
    else if (kind == LED_LAYER_TAP) c = theme_rgb(t->layer[arg], LAYER_TAP_VAL);
    else if (kind == LED_THEME)     c = theme_rgb(themes[arg].layer[0], LAYER_TAP_VAL);
    else                            c = colors[kind];
    rgb_matrix_set_color(i, c.r, c.g, c.b);
  }
}

void keyboard_post_init_user(void) {
  uint32_t saved = eeconfig_read_user();
  current_theme = (saved & 0xFF) < THEME_COUNT ? (saved & 0xFF) : 0;
  current_mode  = ((saved >> 8) & 0x03) <= MODE_DIM ? ((saved >> 8) & 0x03) : MODE_NORMAL;
  find_led_kinds();
  rgb_matrix_enable();
}

void eeconfig_init_user(void) {  // EEPROM reset: back to theme 1, normal brightness
  current_theme = 0;
  current_mode  = MODE_NORMAL;
  eeconfig_update_user(0);
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (!keyboard_config.disable_layer_led) {
    switch (biton32(layer_state)) {
      case 0:
        set_layer_color(0);
        break;
      case 1:
        set_layer_color(1);
        break;
      case 2:
        set_layer_color(2);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}




// The Repeat thumb itself is never the key to repeat.
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
  return keycode != REP_NUM;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case REP_NUM:
    if (record->tap.count) {  // tap = repeat the last key; hold = layer 1 as usual
      repeat_key_invoke(&record->event);
      return false;
    }
    break;
  case DM_KEY1:
  case DM_KEY2:
    // Recording stops on the press (either macro key stops it); record/play
    // start on the release, as the built-in DM_ keys expect.
    // Held longer than TAPPING_TERM = record, shorter = play.
    if (record->event.pressed) {
      dm_timer    = timer_read();
      dm_stopping = dm_recording != 0;
      if (dm_stopping) process_dynamic_macro(QK_DYNAMIC_MACRO_RECORD_STOP, record);
    } else if (!dm_stopping) {
      bool hold = timer_elapsed(dm_timer) >= TAPPING_TERM;
      if (keycode == DM_KEY1) {
        process_dynamic_macro(hold ? QK_DYNAMIC_MACRO_RECORD_START_1 : QK_DYNAMIC_MACRO_PLAY_1, record);
      } else {
        process_dynamic_macro(hold ? QK_DYNAMIC_MACRO_RECORD_START_2 : QK_DYNAMIC_MACRO_PLAY_2, record);
      }
    }
    return false;
  case BSPC_NUM:
    // Shift + tap = Delete (2026-11-06); hold = layer 1 as usual. Done here, not
    // with a key override, because the tap is part of a layer-tap key.
    if (record->tap.count && (get_mods() & MOD_MASK_SHIFT)) {
      if (record->event.pressed) {
        uint8_t mods = get_mods();
        del_mods(MOD_MASK_SHIFT);
        tap_code(KC_DEL);
        set_mods(mods);
      }
      return false;
    }
    break;
  case THEME_1 ... THEME_5:
    if (record->event.pressed) set_theme(keycode - THEME_1);
    return false;
  case LED_BRIGHT:
    if (record->event.pressed) toggle_mode(MODE_BRIGHT);
    return false;
  case LED_DIM:
    if (record->event.pressed) toggle_mode(MODE_DIM);
    return false;
  case QK_MODS ... QK_MODS_MAX:
    // Mouse and consumer keys (volume, media) with modifiers work inconsistently across operating systems,
    // this makes sure that modifiers are always applied to the key that was pressed.
    if (IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
      if (record->event.pressed) {
        add_mods(QK_MODS_GET_MODS(keycode));
        send_keyboard_report();
        wait_ms(2);
        register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
        return false;
      } else {
        wait_ms(2);
        del_mods(QK_MODS_GET_MODS(keycode));
      }
    }
    break;
  }
  return true;
}
