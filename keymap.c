#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

// Local keymap, started from Oryx layout xL0xx/ZPj7mz (2026-10-26).
// Layer 0: Colemak-DH base, 1: numbers and symbols (hold either lower thumb),
// 2: F-keys, arrows, Home/End/PgUp/PgDn, media, QK_BOOT top right (hold Space, as on the laptop).
// Enter: tap = Enter, hold = Meta (xmonad mod), next to Meta on G and M.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           CW_TOGG,
    KC_TAB,         KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,                                           KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCLN,        KC_DELETE,
    KC_BSPC,        KC_A,           MT(MOD_LSFT, KC_R),MT(MOD_LALT, KC_S),MT(MOD_LCTL, KC_T),MT(MOD_LGUI, KC_G),                                         MT(MOD_RGUI, KC_M),MT(MOD_RCTL, KC_N),MT(MOD_LALT, KC_E),MT(MOD_RSFT, KC_I),KC_O,           KC_QUOTE,
    KC_LEFT,        KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                           KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RIGHT,
                                                    LT(2, KC_SPACE),LT(1, KC_DOWN),                                 LT(1, KC_UP),   MT(MOD_RGUI, KC_ENTER)
  ),
  [1] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_BSLS,        KC_EXLM,        KC_TILD,        KC_NO,                                          KC_NO,          KC_NO,          KC_COLN,        KC_PIPE,        KC_NO,          KC_NO,
    KC_MINUS,       KC_PLUS,        KC_LBRC,        KC_LCBR,        KC_LPRN,        KC_UNDS,                                        KC_MINUS,       KC_RPRN,        KC_RCBR,        KC_RBRC,        KC_SCLN,        KC_DQUO,
    KC_EQUAL,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_QUOTE,
    KC_PLUS,        KC_ASTR,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_CIRC,        KC_AMPR,        KC_COMMA,       KC_DOT,         KC_SLASH,       KC_GRAVE,
                                                    KC_SPACE,       KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_ENTER
  ),
  [2] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,
    KC_NO,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_NO,                                          KC_NO,          KC_NO,          KC_F11,         KC_F12,         KC_NO,          KC_NO,
    KC_NO,          KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_NO,
    KC_NO,          KC_HOME,        KC_PGDN,        KC_PAGE_UP,     KC_END,         KC_NO,                                          KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,
                                                    KC_TRANSPARENT, KC_NO,                                          KC_NO,          KC_NO
  ),
};

// Chordal Hold handedness. Outer columns (Esc, Tab, Backspace, arrows, Del, ...)
// and thumbs are '*', so T + Backspace still gives Ctrl+Backspace and
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

// Per-key LED overrides on top of the layer colour. Found from the keymap at
// start-up, so they follow keymap edits. In order of priority:
// - Unused (2026-11-05, per layer since 2026-11-06): KC_NO on the current layer
//   is off, so a held layer shows only the keys that do something there.
//   {0, 0, 0} = off; for a dim colour use e.g. {0, 0, 30} (dim white).
// - Boot (2026-11-06): QK_BOOT (flash mode) is red.
// - Held mod (2026-11-06): a mod-tap key that is pressed and whose modifier is
//   active right now is white on every layer, so you can see a hold became a mod.
// - Groups (2026-11-06), layers 1 and 2 only: numbers yellow, arrows white,
//   Home/End/PgUp/PgDn white, F-keys yellow, media pink. Symbols and other
//   keys keep the layer colour.
// - Mod-tap (2026-11-05): a modifier on hold (MT), i.e. home-row mods and
//   Enter/Meta, is coral. Base layer only since 2026-11-06, so the groups show
//   on layers 1 and 2.
// - Caps Word (2026-11-06), base layer: while Caps Word is on, the letter keys
//   and the Caps Word key are magenta (a held mod still shows white).
// - Layer tap (2026-11-06), base layer: a layer-tap key (LT) shows the colour
//   of the layer it opens, brighter: Space blue, Down/Up violet.
// Voyager first (2026-11-06); the Moonlander still has the 2026-11-05 version.
enum led_kind {
  LED_NORMAL,  // layer colour
  LED_UNUSED, LED_BOOT, LED_MOD_HELD, LED_MOD_TAP,
  LED_NUMBER, LED_ARROW, LED_NAV, LED_FKEY, LED_MEDIA,
  LED_CAPS_WORD,
  LED_LAYER_TAP,  // colour comes from ledmap[target layer], not kind_colors
  LED_KIND_COUNT
};

// {hue, sat, val}; val is scaled by the board brightness keys.
static const uint8_t PROGMEM kind_colors[LED_KIND_COUNT][3] = {
  [LED_UNUSED]   = {  0,   0,   0},  // off
  [LED_BOOT]     = {  0, 255, 255},  // red
  [LED_MOD_HELD] = {  0,   0, 255},  // white
  [LED_MOD_TAP]  = {  8, 255, 255},  // coral (was amber 21), 2026-11-06
  [LED_NUMBER]   = { 43, 255, 230},  // yellow
  [LED_ARROW]    = {  0,   0, 230},  // white (was cyan 128, too close to layer 2 blue)
  [LED_NAV]      = {  0,   0, 230},  // white with the arrows (was blue 160, then layer 2 became blue)
  [LED_FKEY]     = { 43, 255, 230},  // yellow like the numbers (was orange 14, too close to boot red)
  [LED_MEDIA]    = {223, 255, 230},  // pink
  [LED_CAPS_WORD] = {206, 255, 230}, // magenta
};
// Palette 2026-11-06: layer colours 150 (was ~100), highlights 230-255
// (were 160-200), layer 1 violet 191 (was indigo 164, too close to base blue).
// Base layer green and layer 2 blue since 2026-11-06
// (base was blue, then teal; layer 2 was green).
#define LAYER_TAP_VAL 230  // brightness of the layer-tap thumb keys
extern const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3];  // layer colours, below

#define LAYER_COUNT (sizeof(keymaps) / sizeof(keymaps[0]))

static uint8_t led_kind[LAYER_COUNT][RGB_MATRIX_LED_COUNT];
static uint8_t led_mods[RGB_MATRIX_LED_COUNT];  // 8-bit mods of a base-layer MT key, else 0
static keypos_t led_pos[RGB_MATRIX_LED_COUNT];
static bool led_caps_word[RGB_MATRIX_LED_COUNT];  // base-layer letter or CW_TOGG key
static uint8_t led_lt_layer[RGB_MATRIX_LED_COUNT];  // layer a base-layer LT key opens

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
        uint8_t kind;
        if (kc == KC_NO)                     kind = LED_UNUSED;
        else if (kc == QK_BOOT)              kind = LED_BOOT;
        else if (layer > 0)                  kind = group_kind(kc);
        else if (IS_QK_MOD_TAP(base))        kind = LED_MOD_TAP;
        else if (IS_QK_LAYER_TAP(base) &&
                 QK_LAYER_TAP_GET_LAYER(base) < LAYER_COUNT) {
          kind = LED_LAYER_TAP;
          led_lt_layer[led] = QK_LAYER_TAP_GET_LAYER(base);
        }
        else                                 kind = LED_NORMAL;
        led_kind[layer][led] = kind;
      }
    }
  }
}

static void set_key_colors(uint8_t layer) {
  RGB colors[LED_KIND_COUNT];
  for (uint8_t k = 0; k < LED_KIND_COUNT; k++) {
    HSV hsv = {
      .h = pgm_read_byte(&kind_colors[k][0]),
      .s = pgm_read_byte(&kind_colors[k][1]),
      .v = pgm_read_byte(&kind_colors[k][2]),
    };
    colors[k] = hsv_to_rgb_with_value(hsv);
  }
  uint8_t mods = get_mods();
  bool caps_word = layer == 0 && is_caps_word_on();
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    uint8_t kind = led_kind[layer][i];
    if (caps_word && led_caps_word[i]) kind = LED_CAPS_WORD;
    if (kind != LED_UNUSED && kind != LED_BOOT && (mods & led_mods[i]) &&
        matrix_is_on(led_pos[i].row, led_pos[i].col)) {
      kind = LED_MOD_HELD;
    }
    if (kind == LED_NORMAL) continue;
    if (kind == LED_LAYER_TAP) {
      HSV hsv = {
        .h = pgm_read_byte(&ledmap[led_lt_layer[i]][i][0]),
        .s = pgm_read_byte(&ledmap[led_lt_layer[i]][i][1]),
        .v = LAYER_TAP_VAL,
      };
      RGB rgb = hsv_to_rgb_with_value(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      continue;
    }
    rgb_matrix_set_color(i, colors[kind].r, colors[kind].g, colors[kind].b);
  }
}

void keyboard_post_init_user(void) {
  find_led_kinds();
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150}, {87,245,150} },

    [1] = { {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150}, {191,227,150} },

    [2] = { {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150}, {139,184,150} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
  set_key_colors(layer);
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




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
