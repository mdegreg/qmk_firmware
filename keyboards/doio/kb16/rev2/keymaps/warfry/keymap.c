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

#define getarraylength(x) (sizeof(x) / sizeof((x)[0]))

// noop functions for space optimization
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2
};

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
Push rollers start at top left
*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                KC_7,     KC_8,    KC_9,    KC_KP_MINUS,     KC_MUTE,
                KC_4,     KC_5,    KC_6,    KC_KP_PLUS,      TO(_FN),
                KC_1,     KC_2,    KC_3,    KC_ENT,          _______,
                KC_0,     KC_DOT,  KC_LALT,   KC_LSFT
            ),

/*

*/
    /*  Row:    0        1        2        3        4       */
    [_FN] = LAYOUT(
                _______, _______, _______, _______,   _______,
                KC_F1,   KC_F2,   KC_F3,   KC_F4,     TO(_FN1),
                KC_F5,   KC_F6,   KC_F7,   KC_F8,     _______,
                KC_F9,   KC_F10,  KC_F11,  KC_F12
            ),

/*

*/
    /*  Row:    0        1        2        3        4       */
    [_FN1] = LAYOUT(
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN2),
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

/*

*/
    /*  Row:    0        1        2        3        4        */
    [_FN2] = LAYOUT(
                _______, _______, _______, QK_BOOT, _______,
                _______, _______, _______, _______, TO(_BASE),
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_BASE] = {
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_LIGHTBLUE},
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_LIGHTBLUE},
        {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_CHILLGREEN},
        {HSV_WHITE}, {HSV_LIGHTBLUE}, {HSV_ORANGE}, {HSV_MAGENTA}
    },
    [_FN] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN},
        {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN}
    },
    [_FN1] = {
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}
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
    [_BASE] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
