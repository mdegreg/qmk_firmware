#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#ifdef ORYX_ENABLE
#include "oryx.h"
#endif

#include "version.h"
#include "alttab.h"
#include "modifiers.h"
#include "os_swap.h"
#include "dances.h"
#include "dances_taptypes.h"
#include "dances_user.h"
#include "layers_user.h"
#include "ledmap_user.h"
#include "layout_user.h"
#include "callbacks.h"
#include "custom_keycodes.h"

#if CONSOLE_ENABLE
#include "print.h"
#include "os_detection.h"
#endif

#define getarraylength(x) (sizeof(x) / sizeof((x)[0]))

uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}

extern rgb_config_t rgb_matrix_config;

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

HSV os_color_win = {HSV_RED};
HSV os_color_mac = {HSV_CHILLGREEN};
HSV (*os_indicator_hsv_color) = {&os_color_win};

layer_state_t layer_state_set_user(layer_state_t state) {
# ifdef ORYX_ENABLE
  layer_state_set_oryx(state);
# endif
  if (layer_state_is(OS_MAC_LAYOUT)){
    set_os(OS_MACOS);
    os_indicator_hsv_color = &os_color_mac;
  } else {
    set_os(OS_WINDOWS);
    os_indicator_hsv_color = &os_color_win;
  }
  return state;
}

bool rgb_matrix_indicators_user(void) {
    int current_layer;

    if (keyboard_config.disable_layer_led) { return true; }

    current_layer = biton32(layer_state);
    if (0 <= current_layer && current_layer <= getarraylength(ledmap)) {
        set_layer_color(current_layer);
    } else if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
    }
    return false;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_caps_lock_on() && (get_highest_layer(layer_state) != UTIL_LAYOUT)) {
        rgb_matrix_set_color(2, RGB_RED);
    }

    if (is_num_lock_on() && (get_highest_layer(layer_state) == NUMKEYS_LAYOUT)) {
        rgb_matrix_set_color(56, RGB_RED);
    }

    RGB os_indicator_rgb_color = hsv_to_rgb(*os_indicator_hsv_color);
    if (layer_state_is(FKEYS_LAYOUT)) {
        rgb_matrix_set_color(
            24,
            (os_indicator_rgb_color).r,
            (os_indicator_rgb_color).g,
            (os_indicator_rgb_color).b
        );
        rgb_matrix_set_color(
            60,
            (os_indicator_rgb_color).r,
            (os_indicator_rgb_color).g,
            (os_indicator_rgb_color).b
        );
    };
    if (layer_state_is(NUMKEYS_LAYOUT)) {
        rgb_matrix_set_color(
            19,
            (os_indicator_rgb_color).r,
            (os_indicator_rgb_color).g,
            (os_indicator_rgb_color).b
        );
    };
    if (get_highest_layer(layer_state) != UTIL_LAYOUT) {
        rgb_matrix_set_color(
            40,
            (os_indicator_rgb_color).r,
            (os_indicator_rgb_color).g,
            (os_indicator_rgb_color).b
        );
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ORYX_ENABLE
  process_record_oryx(keycode, record);
#endif
#if CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n",
            keycode,
            record->event.key.col,
            record->event.key.row,
            record->event.pressed,
            record->event.time,
            record->tap.interrupted,
            record->tap.count
    );


    switch (keycode) {
    }
#endif
  switch (keycode) {
#if CONSOLE_ENABLE
    case STORE_SETUPS:
        if (record->event.pressed) {
            store_setups_in_eeprom();
        }
        return false;
    case PRINT_SETUPS:
        if (record->event.pressed) {
            print_stored_setups();
        }
        return false;
#endif
    default:
      return true;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
    timeout_super_alt_tab();
}
