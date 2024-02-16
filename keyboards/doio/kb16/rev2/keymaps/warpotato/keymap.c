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

#include "alttab.h"
#include "os_swap.h"
#include "dances.h"
#include "dances_user.h"
#include "layers_user.h"
#include "layout_user.h"
#include "ledmap_user.h"

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

// 1st layer on the cycle
#define LAYER_CYCLE_START _BASE
// Last layer on the cycle
#define LAYER_CYCLE_END NUM_LAYERS - 1

// enum layer_keycodes { };

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

void matrix_scan_user(void) { // The very important timer.
    timeout_super_alt_tab();
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_CYCLE_LAYERS_L, KC_CYCLE_LAYERS_R), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [NAVARROW]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_ARROW]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [PYCHARM]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [VSCODE]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [SONAR]   = { ENCODER_CCW_CW(A(KC_KP_PLUS), A(KC_KP_MINUS)), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
