/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// OLED animation
#include "./lib/layer_status/layer_status.h"

#include "os_swap.h"
#include "dances.h"

#define getarraylength(x) (sizeof(x) / sizeof((x)[0]))

// noop functions for space optimization
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}


uint32_t os_detection_callback(uint32_t trigger_time, void* cb_arg) {
  os_variant_t current_os = detected_host_os();
  if (current_os == OS_MACOS) {
    set_os(OS_MACOS);
  } else {
    set_os(OS_WINDOWS);
  }
  return 0;
}


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  #if CONSOLE_ENABLE
  debug_enable=true;
  debug_keyboard=true;
    #if MOUSEKEY_ENABLE
    debug_mouse=true;
    #endif
  #endif
  rgb_matrix_enable();
  defer_exec(1000, os_detection_callback, NULL);
  #if CONSOLE_ENABLE

    uprintf("OS: %2u\n",
            current_os
    );
  #endif

#ifdef OLED_ENABLE
#endif
}

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    SONAR,
    _ARROW,
    PYCHARM,
    VSCODE,
    _FN,
    _FN2,
    NUM_LAYERS,
};
// 1st layer on the cycle
#define LAYER_CYCLE_START _BASE
// Last layer on the cycle
#define LAYER_CYCLE_END NUM_LAYERS - 1

enum tap_dance_codes {
  DNC_LEFT,
  DNC_RIGHT,
  /*
  ** Do not change or move from bottom of enum. **

  An enum by default has the value 0 for the
  first value, incrementing by 1 each time.

  Leaving this as is will take advantage of that,
  as the last item will be equal to the length of
  the array of items above, e.g. the bottom value
  will be the number of items excluding itself.

  We use the last item here to indicate dynamically
  how many tap dance functions we support within this keymap.
  */
  MAX_COUNT_TAPDANCES,
};

enum keycodes {
    KC_CYCLE_LAYERS_R = SAFE_RANGE,
    KC_CYCLE_LAYERS_L,
    VSC_PUSH,
    VSC_COMMIT,
    VSC_PULL,
};

tap_dance_action_t tap_dance_actions[];
tap dance_state[MAX_COUNT_TAPDANCES];

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
Push rollers start at top left
*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                KC_7,     KC_8,    KC_9,    KC_KP_MINUS,     KC_MUTE,
                KC_4,     KC_5,    KC_6,    KC_KP_PLUS,      _______,
                KC_1,     KC_2,    KC_3,    KC_ENT,          _______,
                KC_0,     KC_DOT,  KC_BSPC,   KC_LSFT
            ),
/*

*/
    /*  Row:    0        1        2        3        4       */
    [SONAR] = LAYOUT(
                C(KC_KP_DOT), C(KC_KP_MINUS), C(KC_KP_PLUS), _______, S(KC_F8),
                C(KC_KP_3), C(KC_KP_9), C(KC_KP_6), _______, _______,
                C(KC_KP_2), C(KC_KP_8), C(KC_KP_5), _______, _______,
                C(KC_KP_1), C(KC_KP_7), C(KC_KP_4), _______
            ),
    /*  Row:    0        1        2        3        4       */
    [_ARROW] = LAYOUT(
                _______, _______, _______, _______, KC_MUTE,
                _______, _______, _______, _______, _______,
                _______, KC_UP,   C(KC_C), KC_ENT, _______,
                TD(DNC_LEFT), KC_DOWN, TD(DNC_RIGHT), _______
            ),

    /*  Row:    0        1        2        3        4        */
    [PYCHARM] = LAYOUT(
                KC_F1, LGUI(KC_B), _______, LCTL(KC_T), _______,
                LSG(KC_BSPC), _______, _______, LSG(KC_K), _______,
                C(S(KC_UP)), _______, _______, LGUI(KC_K), _______,
                C(S(KC_DOWN)), _______, _______, LGUI(KC_T)
            ),

    /*  Row:    0        1        2        3        4        */
    [VSCODE] = LAYOUT(
                _______, _______, _______, _______, _______,
                _______, _______, _______, VSC_PUSH, _______,
                _______, _______, _______, VSC_COMMIT, _______,
                _______, _______, _______, VSC_PULL
            ),

    /*  Row:    0        1        2        3        4       */
    [_FN] = LAYOUT(
                _______, _______, _______, _______,   _______,
                KC_F1,   KC_F2,   KC_F3,   KC_F4,     _______,
                KC_F5,   KC_F6,   KC_F7,   KC_F8,     _______,
                KC_F9,   KC_F10,  KC_F11,  KC_F12
            ),

    /*  Row:    0        1        2        3        4        */
    [_FN2] = LAYOUT(
                _______, _______, _______, QK_BOOT, _______,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),
};

const char * layer_names[] = {
    "Base",
    "Sonar",
    "Arrow",
    "Pycharm",
    "VSCode",
    "Fn",
    "Util",
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        uint8_t current_layer = get_highest_layer(layer_state);
        oled_set_cursor(2, 1);
        oled_write_ln(PSTR(layer_names[current_layer]), false);
        return true;
    }
#endif


void on_cw_spin(void);
void on_ccw_spin(void);

void on_cw_spin(void) {
      uint8_t current_layer = get_highest_layer(layer_state);
      int8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
}

void on_ccw_spin(void) {
      uint8_t current_layer = get_highest_layer(layer_state);
      int8_t next_layer = current_layer - 1;
      if (next_layer < LAYER_CYCLE_START) {
          next_layer = LAYER_CYCLE_END;
      }
      layer_move(next_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CYCLE_LAYERS_R:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) {
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }
      on_cw_spin();
      return false;
    case KC_CYCLE_LAYERS_L:
      if (!record->event.pressed) {
        return false;
      }
      on_ccw_spin();
      return false;
    case VSC_PUSH:
      if (!record->event.pressed) {
        return false;
      }
      SEND_STRING(SS_LALT("gp"));
      return false;
    case VSC_COMMIT:
      if (!record->event.pressed) {
        return false;
      }
      SEND_STRING(SS_LALT("gc"));
      return false;
    case VSC_PULL:
      if (!record->event.pressed) {
        return false;
      }
      SEND_STRING(SS_LALT("gu"));
      return false;

    // Process other keycodes normally
    default:
      return true;
  }
}


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_BASE] = {
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_LIGHTBLUE},
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_LIGHTBLUE},
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_CHILLGREEN},
        {HSV_WHITE}, {HSV_LIGHTBLUE}, {HSV_RED}, {HSV_MAGENTA}
    },
    [SONAR] = {
        {HSV_MINTGREEN}, {HSV_RED}, {HSV_CHILLGREEN}, {HSV_OFF},
        {HSV_LIGHTBLUE}, {HSV_RED}, {HSV_CHILLGREEN}, {HSV_OFF},
        {HSV_MAGENTA}, {HSV_RED}, {HSV_CHILLGREEN}, {HSV_OFF},
        {HSV_PURPLE}, {HSV_RED}, {HSV_CHILLGREEN}, {HSV_OFF}
    },
    [_ARROW] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_MINTGREEN}, {HSV_RED}, {HSV_CHILLGREEN},
        {HSV_MINTGREEN}, {HSV_MINTGREEN}, {HSV_MINTGREEN}, {HSV_OFF}
    },
    [PYCHARM] = {
        {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_OFF}, {HSV_ORANGE},
        {HSV_RED}, {HSV_OFF}, {HSV_OFF}, {HSV_CHILLGREEN},
        {HSV_LIGHTBLUE}, {HSV_OFF}, {HSV_OFF}, {HSV_CHILLGREEN},
        {HSV_LIGHTBLUE}, {HSV_OFF}, {HSV_OFF}, {HSV_LIGHTBLUE}
    },
    [VSCODE] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CHILLGREEN},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_CHILLGREEN},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_PURPLE}
    },
    [_FN] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}
    },
    [_FN2] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_RED},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}
    }
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
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
    int current_layer;

    current_layer = biton32(layer_state);
    if (0 <= current_layer && current_layer <= getarraylength(ledmap)) {
        set_layer_color(current_layer);
    } else if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
    }
    return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_CYCLE_LAYERS_L, KC_CYCLE_LAYERS_R), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [SONAR]   = { ENCODER_CCW_CW(S(KC_F9), S(KC_F10)), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_ARROW]   = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [PYCHARM]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [VSCODE]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

// bump left or right by a full word on hold`
void on_dance_la(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_LEFT, KC_LEFT, os_bksp_mod
    );
}

void dance_la_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        &(dance_state[DNC_LEFT]), state, KC_LEFT, KC_LEFT, os_bksp_mod
    );
}

void dance_la_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        &(dance_state[DNC_LEFT]), state, KC_LEFT, KC_LEFT, os_bksp_mod
    );
}

void on_dance_ra(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_RIGHT, KC_RIGHT, os_bksp_mod
    );
}

void dance_ra_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        &(dance_state[DNC_RIGHT]), state, KC_RIGHT, KC_RIGHT, os_bksp_mod
    );
}

void dance_ra_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        &(dance_state[DNC_RIGHT]), state, KC_RIGHT, KC_RIGHT, os_bksp_mod
    );
}

tap_dance_action_t tap_dance_actions[] = {
        [DNC_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_la, dance_la_finished, dance_la_reset),
        [DNC_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ra, dance_ra_finished, dance_ra_reset),
};
