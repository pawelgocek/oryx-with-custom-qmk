#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  KC_PANIC,   // clear all stuck modifiers and layers
};



#define DUAL_FUNC_0 LT(2, KC_F24)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Layer 0 - Base (QWERTY)
   *
   * ,------+------+------+------+------+------.  ,------+------+------+------+------+------.
   * |      |      |      |      |      |      |  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |  CW  |  Q   |  W   |  E   |  R   |  T   |  |  Y   |  U   |  I   |  O   |  P   |\~/NW |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Tab  |A/Sft |S/Ctl |D/Alt |F/Gui |  G   |  |  H   |J/Gui |K/Alt |L/Ctl |;/Sft | '/L2 |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |  `   |  Z   |  X   |  C   |  V   |  B   |  |  N   |  M   |  ,   |  .   |  /   |      |
   * `------+------+------+------+------+------'  `------+------+------+------+------+------'
   *                              | Esc/L1 | Ent/Gui |  | Bsp/L2 | Spc/L1 |
   *                              `--------+---------'  `--------+--------'
   *
   * CW = hold for CapsWord
   * '/L2 = tap ', hold → lock layer 1 (DUAL_FUNC_0)
   * \~/NW = tap \, hold → toggle NumWord (layer 1, green; exits on space/enter or hold again)
   */
  [0] = LAYOUT_voyager(
    KC_PANIC,            KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,             KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,
    LT(0, KC_NO),        KC_Q,                 KC_W,                 KC_E,                 KC_R,                 KC_T,                       KC_Y,                 KC_U,                 KC_I,                 KC_O,                 KC_P,                 LT(0, KC_BSLS),
    KC_TAB,              MT(MOD_LSFT, KC_A),   MT(MOD_LCTL, KC_S),   MT(MOD_LALT, KC_D),   MT(MOD_LGUI, KC_F),   KC_G,                       KC_H,                 MT(MOD_RGUI, KC_J),   MT(MOD_RALT, KC_K),   MT(MOD_RCTL, KC_L),   MT(MOD_RSFT, KC_SCLN), DUAL_FUNC_0,
    KC_GRAVE,            KC_Z,                 KC_X,                 KC_C,                 KC_V,                 KC_B,                       KC_N,                 KC_M,                 KC_COMMA,             KC_DOT,               KC_SLASH,             KC_TRANSPARENT,
                                                                     LT(1, KC_ESCAPE),     MT(MOD_LGUI, KC_ENTER),                           LT(2, KC_BSPC),      LT(1, KC_SPACE)
  ),
  /*
   * Layer 1 - Numbers & Symbols
   *
   * ,------+------+------+------+------+------.  ,------+------+------+------+------+------.
   * |      |      |      |      |      |      |  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |  1   |  2   |  3   |  4   |  5   |  |  &   |  +   |  (   |  )   |  *   |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |6/Sft |7/Ctl |8/Alt |9/Gui |  0   |  |  =   |-/Gui |[/Alt |]/Ctl |      | TO(0)|
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |  !   |  @   |  #   |  $   |  %   |  |  ^   |  _   |      |      |      |      |
   * `------+------+------+------+------+------'  `------+------+------+------+------+------'
   *                              | TO(0)  |         |  |        |        |
   *                              `--------+---------'  `--------+--------'
   */
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,             KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,
    KC_TRANSPARENT,       KC_1,                 KC_2,                 KC_3,                 KC_4,                 KC_5,                       KC_AMPR,              KC_PLUS,              KC_LPRN,              KC_RPRN,              KC_ASTR,              KC_TRANSPARENT,
    KC_TRANSPARENT,       MT(MOD_LSFT, KC_6),   MT(MOD_LCTL, KC_7),   MT(MOD_LALT, KC_8),   MT(MOD_LGUI, KC_9),   KC_0,                       KC_EQUAL,             MT(MOD_RGUI, KC_MINUS), MT(MOD_RALT, KC_LBRC), MT(MOD_RCTL, KC_RBRC), KC_TRANSPARENT,       TO(0),
    KC_TRANSPARENT,       KC_EXLM,              KC_AT,                KC_HASH,              KC_DLR,               KC_PERC,                    KC_CIRC,              KC_UNDS,              KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,
                                                                      TO(0),                KC_TRANSPARENT,                                   KC_TRANSPARENT,       KC_TRANSPARENT
  ),
  /*
   * Layer 2 - Navigation, F-keys & Media
   *
   * ,------+------+------+------+------+------.  ,------+------+------+------+------+------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |      |      | Play |      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |  F7  |  F8  |  F9  | F10  | F11  | F12  |  |      | Prev |  Up  | Next |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |RGB-  |RGBtog|RGB+  |      |  |      | Left | Down |Right |  F9  |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |  |      | Vol- | Mute | Vol+ |      |      |
   * `------+------+------+------+------+------'  `------+------+------+------+------+------'
   *                              |        |         |  |        |        |
   *                              `--------+---------'  `--------+--------'
   */
  [2] = LAYOUT_voyager(
    KC_F1,                KC_F2,                KC_F3,                KC_F4,                KC_F5,                KC_F6,                      KC_TRANSPARENT,       KC_TRANSPARENT,       KC_MEDIA_PLAY_PAUSE,  KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,
    KC_F7,                KC_F8,                KC_F9,                KC_F10,               KC_F11,               KC_F12,                     KC_TRANSPARENT,       KC_MEDIA_PREV_TRACK,  KC_UP,                KC_MEDIA_NEXT_TRACK,  KC_TRANSPARENT,       KC_TRANSPARENT,
    KC_TRANSPARENT,       KC_TRANSPARENT,       RGB_VAD,              RGB_TOG,              RGB_VAI,              KC_TRANSPARENT,             KC_TRANSPARENT,       KC_LEFT,              KC_DOWN,              KC_RIGHT,             KC_F9,                KC_TRANSPARENT,
    KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,       KC_TRANSPARENT,             KC_TRANSPARENT,       KC_AUDIO_VOL_DOWN,    KC_AUDIO_MUTE,        KC_AUDIO_VOL_UP,      KC_TRANSPARENT,       KC_TRANSPARENT,
                                                                      KC_TRANSPARENT,       KC_TRANSPARENT,                                   KC_TRANSPARENT,       KC_TRANSPARENT
  ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 
  'L', 'L', 'R', 'R'
);




extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

static bool num_word_active = false;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {0,245,245}, {70,254,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {70,254,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {139,219,204}, {201,255,255}, {139,219,204}, {0,0,0}, {0,0,0}, {0,0,0}, {201,255,255}, {201,255,255}, {201,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {37,255,255}, {0,241,226}, {70,254,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

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
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  // sync num_word_active if user exited layer 1 via TO(0) or panic
  if (num_word_active && biton32(layer_state) != 1) {
      num_word_active = false;
  }
  if (is_caps_word_on()) {
      rgb_matrix_set_color_all(255, 80, 0);  // orange while CapsWord is active
      return true;
  }
  if (num_word_active) {
      rgb_matrix_set_color_all(0, 180, 0);  // green while NumWord is active
      uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
      if (mods & MOD_MASK_SHIFT) {
          rgb_matrix_set_color(13, 255, 255, 255);
          rgb_matrix_set_color(42, 255, 255, 255);
      }
      if (mods & MOD_MASK_CTRL) {
          rgb_matrix_set_color(14, 255, 255, 255);
          rgb_matrix_set_color(41, 255, 255, 255);
      }
      if (mods & MOD_MASK_ALT) {
          rgb_matrix_set_color(15, 255, 255, 255);
          rgb_matrix_set_color(40, 255, 255, 255);
      }
      if (mods & MOD_MASK_GUI) {
          rgb_matrix_set_color(16, 255, 255, 255);
          rgb_matrix_set_color(39, 255, 255, 255);
      }
      return true;
  }
  if (!keyboard_config.disable_layer_led) {
    switch (biton32(layer_state)) {
      case 1:
        rgb_matrix_set_color_all(0, 0, 40);  // dim blue while on layer 1
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

  // Highlight active modifiers on their home row keys
  // LED positions: A=13 S=14 D=15 F=16 (left), J=39 K=40 L=41 ;=42 (right)
  uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
  if (mods & MOD_MASK_SHIFT) {
      rgb_matrix_set_color(13, 255, 255, 255);  // A/Shift
      rgb_matrix_set_color(42, 255, 255, 255);  // ;/Shift
  }
  if (mods & MOD_MASK_CTRL) {
      rgb_matrix_set_color(14, 255, 255, 255);  // S/Ctrl
      rgb_matrix_set_color(41, 255, 255, 255);  // L/Ctrl
  }
  if (mods & MOD_MASK_ALT) {
      rgb_matrix_set_color(15, 255, 255, 255);  // D/Alt
      rgb_matrix_set_color(40, 255, 255, 255);  // K/Alt
  }
  if (mods & MOD_MASK_GUI) {
      rgb_matrix_set_color(16, 255, 255, 255);  // F/Gui
      rgb_matrix_set_color(39, 255, 255, 255);  // J/Gui
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

    case KC_PANIC:
      if (record->event.pressed) {
          clear_mods();
          clear_weak_mods();
          clear_oneshot_mods();
          layer_clear();
          send_keyboard_report();
      }
      return false;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_QUOTE);
        } else {
          unregister_code16(KC_QUOTE);
        }
      } else {
        if (record->event.pressed) {
          layer_move(1);
        } else {
          layer_move(1);
        }  
      }  
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;

    case LT(0, KC_NO):
      if (!record->tap.count && record->event.pressed) {
          caps_word_on();
      }
      return false;

    case LT(0, KC_BSLS):
      if (record->tap.count > 0) {
          // tap: backslash
          if (record->event.pressed) register_code(KC_BSLS);
          else unregister_code(KC_BSLS);
      } else if (record->event.pressed) {
          // hold: toggle NumWord
          if (num_word_active) {
              num_word_active = false;
              layer_move(0);
          } else {
              num_word_active = true;
              layer_move(1);
          }
      }
      return false;

    case LT(1, KC_SPACE):
      // Exit NumWord on space tap (layer 1 is transparent at this position, falls through)
      if (num_word_active && record->tap.count > 0 && !record->event.pressed) {
          num_word_active = false;
          layer_move(0);
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
          return false;
      }
      break;

    case MT(MOD_LGUI, KC_ENTER):
      // Exit NumWord on enter tap
      if (num_word_active && record->tap.count > 0 && !record->event.pressed) {
          num_word_active = false;
          layer_move(0);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
          return false;
      }
      break;

  }
  return true;
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    // Exceptionally allow some one-handed chords for hotkeys.
    switch (tap_hold_keycode) {
        case MT(MOD_LGUI, KC_ENTER):
            return true;
        case LT(1,KC_ESCAPE):
            return true;
        case LT(2,KC_BSPC):
            return true;
        case LT(1, KC_SPACE):
            return true;
        //case KC_SPACE:
        //    return false;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_ENTER):
            // Immediately select the hold action when another key is pressed.
            return true;
        case LT(1,KC_ESCAPE):
            return true;
        case MT(MOD_RSFT, KC_SCLN):
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
