#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#ifdef ORYX_ENABLE
#include "oryx.h"
#endif

#include "version.h"

#ifndef SUPER_ALT_TAB_INITIALIZED
#include "alttab.h"
#endif

#include "modifiers.h"

#ifndef OS_SWAP_INITIALIZED
#include "os_swap.h"
#endif

#ifndef DANCES_INITIALIZED
#include "dances.h"
#endif

#ifndef DANCES_TAPTYPES_INITIALIZED
#include "dances_taptypes.h"
#endif

#if CONSOLE_ENABLE
#include "print.h"
#endif

#define getarraylength(x) (sizeof(x) / sizeof((x)[0]))

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE,
  WK_PYTYPEDEF,
};

enum {
    OS_WIN_LAYOUT,
    OS_MAC_LAYOUT,
    GAMING_LAYOUT,
    NUMKEYS_GAMING,
    FKEYS_GAMING,
    NUMKEYS_LAYOUT,
    FKEYS_LAYOUT,
    UTIL_LAYOUT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [OS_WIN_LAYOUT] = LAYOUT_moonlander(
      // baseline layout - mostly qwerty, with some keys shifted to emphasize
      // left hand typing + habitual movements
    TD(DNC_ESC_LS),         KC_1,           KC_2,           KC_3,               KC_4,           KC_5,                           KC_6,                           KC_BSPC,    KC_7,        KC_8,                  KC_9,       KC_0,      KC_TRANSPARENT, KC_PGUP,
    KC_TAB,                 KC_Q,           KC_W,           KC_E,               KC_R,           KC_T,                           KC_Y,                           KC_EQUAL,   KC_U,        KC_I,                  KC_O,       KC_P,      KC_BSLS,        KC_PGDN,
    KC_CAPS_LOCK,           KC_A,           KC_S,           KC_D,               TD(DNC_FIND),   KC_G,                           KC_H,                           KC_MINUS,   KC_J,        KC_K,                  KC_L,       KC_SCLN,   KC_QUOTE,       KC_TRANSPARENT,
    SC_LSPO,                KC_Z,           TD(DNC_XCUT),   TD(DNC_COPY),       TD(DNC_CPS),    KC_B,                                                                       KC_N,        KC_M,                  KC_COMMA,   KC_DOT,    KC_SLASH,       SC_RSPC,
    MT(MOD_LCTL, KC_GRAVE), KC_LALT,        TD(DNC_RTN_L0), TT(NUMKEYS_LAYOUT), TT(FKEYS_LAYOUT),                               TD(DNC_BACKSPACE),              TD(DNC_BACKSPACE),       TD(DNC_RH_FNSWAP),     KC_LBRC,    KC_RBRC,   KC_TRANSPARENT, KC_LGUI,
                                                                                TD(DNC_SPC),    LT(NUMKEYS_LAYOUT, KC_ENTER),   TD(DNC_SUPER_ALT_TAB),          MT(MOD_LALT, KC_QUOTE),  MT(MOD_LCTL, KC_DOT),  MT(MOD_LSFT, KC_EQUAL)
  ),
  [OS_MAC_LAYOUT] = LAYOUT_moonlander(
      // minor modifications for mac os; most are handled via generic tapdance defs,
      // but ctrl/cmd swapping and layer switch cue are replaced here for simplicity 
      // keeping this layer is handy for catching and triggering os-specific
      // keypress interception, even if its mostly duplicative
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                 KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    MT(MOD_LGUI, KC_GRAVE), KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT,                         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LCTL,
                                                                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, MT(MOD_LGUI, KC_DOT),   KC_TRANSPARENT
  ),
  [NUMKEYS_LAYOUT] = LAYOUT_moonlander(
      // phone-style numpad plus arrowkey layer
    KC_TRANSPARENT,     KC_1,           KC_2,           KC_3,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_4,           KC_5,           KC_6,           KC_TRANSPARENT, KC_TRANSPARENT, KC_PGUP,                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_7,           KC_8,           KC_9,           KC_UP,          C(KC_C),        KC_PGDN,                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_TRANSPARENT, KC_0,           TD(DNC_LEFT),   KC_DOWN,        TD(DNC_RIGHT),                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT,                   KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [FKEYS_LAYOUT] = LAYOUT_moonlander(
      // traditional 10 key numpad plus fn-key access, general layout
    KC_TRANSPARENT,         KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                          KC_TRANSPARENT, KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                           KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         S(KC_1),        S(KC_2),        S(KC_3),        S(KC_4),        S(KC_5),        S(KC_6),                        KC_TRANSPARENT, S(KC_7),        S(KC_8),        S(KC_9),        S(KC_0),        KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, TD(DNC_CURLY),  TD(DNC_SQUARE), KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [GAMING_LAYOUT] = LAYOUT_moonlander(
      // gaming layout; adding additional access for number keys and
      // eliminating most tapdance options to reduce input lag.
      // set up to allow easy access for number and fn key layers
    KC_ESCAPE,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
    KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_7,                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
    KC_NO,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_F,           KC_TRANSPARENT, KC_8,                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_LSFT,         KC_TRANSPARENT, KC_X,           KC_C,               KC_V,           KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_LCTL,         KC_LALT,        KC_TRANSPARENT, MO(NUMKEYS_GAMING), MO(FKEYS_GAMING),               KC_BSPC,                        KC_BSPC,                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                         KC_SPACE,       KC_ENTER,       KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [FKEYS_GAMING] = LAYOUT_moonlander(
      // traditional 10 key numpad plus fn-key access, gaming layout
    KC_TRANSPARENT,  KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,                         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT, KC_0,           KC_PGUP,        KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_PGDN,        KC_MINUS,       KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                     KC_TAB,         KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [NUMKEYS_GAMING] = LAYOUT_moonlander(
      // phone-style numpad plus arrowkey layer
    KC_TRANSPARENT,     KC_1,           KC_2,           KC_3,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_4,           KC_5,           KC_6,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_7,           KC_8,           KC_9,           KC_UP,          KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_TRANSPARENT, KC_0,           KC_LEFT,        KC_DOWN,        KC_RIGHT,                                         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT,                   KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [UTIL_LAYOUT] = LAYOUT_moonlander(
      // Quick access for momentary toggle off of base layer
    TD(DNC_BOOTLOADER),     KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_NUM_LOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_NO,          KC_TRANSPARENT,
    KC_AUDIO_VOL_UP,        KC_MEDIA_PREV_TRACK,    KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_TRANSPARENT,
    KC_AUDIO_VOL_DOWN,      KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     KC_TRANSPARENT,
    KC_AUDIO_MUTE,          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_ENTER,    KC_TRANSPARENT,
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_TRANSPARENT,                 KC_KP_0,        KC_KP_0,        KC_KP_DOT,      KC_KP_ENTER,    KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  #if CONSOLE_ENABLE
  debug_enable=true;
  debug_keyboard=true;
  //debug_mouse=true;
  #endif
  rgb_matrix_enable();
}

// LEDs are assigned top-down by column, approximately, from outside to inside,
// starting with the left half of the keyboard.
const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [OS_WIN_LAYOUT] = {
        // main keys - left
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_ORANGE}, // 4
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_ORANGE}, // 9
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_RED}, // 14
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 19
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 24
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 28
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, // 31

        // thumb keys
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE}, // 34
        {HSV_RED}, // left red key 35

        // main keys - right
        // note that these start from the rightmost column
        {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_RED}, // 40
        {HSV_OFF}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_OFF}, // 45
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 50
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 55
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 60
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, // 64
        {HSV_RED}, {HSV_YELLOW}, {HSV_YELLOW}, // 67

        // thumb keys
        {HSV_MAGENTA}, {HSV_ORANGE}, {HSV_ORANGE}, // 70
        {HSV_RED}  // right red key, 71
    },

    [OS_MAC_LAYOUT] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_CHILLGREEN},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},

        {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_CHILLGREEN},
        {HSV_OFF}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_OFF},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_RED}, {HSV_YELLOW}, {HSV_YELLOW},
        {HSV_MAGENTA}, {HSV_ORANGE}, {HSV_ORANGE},
        {HSV_RED}
    },

    [NUMKEYS_LAYOUT] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_OFF}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_MINTGREEN}, {HSV_MINTGREEN}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_RED}, {HSV_MINTGREEN},
        {HSV_OFF}, {HSV_GREEN}, {HSV_GREEN},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},

        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_MAGENTA}, {HSV_ORANGE}, {HSV_ORANGE},
        {HSV_OFF}
    },

    [FKEYS_LAYOUT] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_OFF}, {HSV_ORANGE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_OFF}, {HSV_WHITE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_OFF},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},
               
        {HSV_GREEN}, {HSV_GREEN}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_CHILLGREEN},
        {HSV_OFF}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_OFF},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_OFF}, {HSV_OFF},
        {HSV_GREEN}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_OFF},
        {HSV_RED}, {HSV_YELLOW}, {HSV_YELLOW},
        {HSV_MAGENTA}, {HSV_ORANGE}, {HSV_ORANGE},
        {HSV_RED}
    },

    [GAMING_LAYOUT] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_RED}, {HSV_WHITE}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_RED}, {HSV_RED}, {HSV_WHITE}, {HSV_COOLWHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_RED}, {HSV_WHITE}, {HSV_COOLWHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_COOLWHITE},
        {HSV_ICEBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},

        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}
    },

    [FKEYS_GAMING] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_OFF}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_RED}, {HSV_OFF}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_GREEN}, {HSV_GREEN}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_YELLOW}, {HSV_YELLOW}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_OFF}, {HSV_OFF},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_OFF},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},

        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}
    },

    [NUMKEYS_GAMING] = {
        {HSV_ORANGE}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_MAGENTA}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_OFF}, {HSV_ORANGE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_WHITE},
        {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_ICEBLUE}, {HSV_MINTGREEN}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_MINTGREEN}, {HSV_MINTGREEN}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_MINTGREEN},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_WHITE},
        {HSV_RED},

        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}
    },

    [UTIL_LAYOUT] = {
        {HSV_RED}, {HSV_LIGHTBLUE}, {HSV_ORANGE}, {HSV_RED}, {HSV_OFF},
        {HSV_OFF}, {HSV_ORANGE}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_SEAGREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_WHITE},
        {HSV_OFF}, {HSV_SEAGREEN}, {HSV_OFF}, {HSV_OFF}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF},

        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_LIGHTBLUE}, {HSV_LIGHTBLUE}, {HSV_CHILLGREEN}, {HSV_CHILLGREEN},
        {HSV_LIGHTBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_LIGHTBLUE},
        {HSV_LIGHTBLUE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_OFF},
        {HSV_SEAGREEN}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE}, {HSV_WHITE},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_RED}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}, {HSV_OFF}, {HSV_OFF},
        {HSV_OFF}
    },

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

HSV os_color_win = {HSV_RED};
HSV os_color_mac = {HSV_CHILLGREEN};
HSV (*os_indicator_hsv_color) = {&os_color_win};

layer_state_t layer_state_set_user(layer_state_t state) {
# ifdef ORYX_ENABLE
  layer_state_set_oryx(state);
# endif
  if (layer_state_is(OS_MAC_LAYOUT)){
    set_os(OS_MAC);
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
  
    if (is_num_lock_on() && get_highest_layer(layer_state) == UTIL_LAYOUT){
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
#endif
  switch (keycode) {
    default:
      return true;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
    timeout_super_alt_tab();
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}
void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_ESC_LS].step = dance_step(state);
    switch (dance_state[DNC_ESC_LS].step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: register_code16(KC_ESCAPE); register_code16(KC_ESCAPE); break;
        case DOUBLE_HOLD:
            layer_on(GAMING_LAYOUT);
            break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_ESC_LS].step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state[DNC_ESC_LS].step = 0;
}

void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_F);
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(state, KC_F, DNC_FIND);
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(state, KC_F, DNC_FIND);
}

void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_X);
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(state, KC_X, DNC_XCUT);
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(state, KC_X, DNC_XCUT);
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_C);
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(state, KC_C, DNC_COPY);
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(state, KC_C, DNC_COPY);
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_V);
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(state, KC_V, DNC_CPS);
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(state, KC_V, DNC_CPS);
}

void on_dance_7(tap_dance_state_t *state, void *user_data);
void dance_7_finished(tap_dance_state_t *state, void *user_data);
void dance_7_reset(tap_dance_state_t *state, void *user_data);

void on_dance_7(tap_dance_state_t *state, void *user_data) {
    on_charswap_dance(state, KC_SPACE, KC_UNDS, DNC_SPC);
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(state, KC_SPACE, KC_UNDS, DNC_SPC);
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(state, KC_SPACE, KC_UNDS, DNC_SPC);
}

void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

void on_dance_8(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        trigger_super_alt_tab(true);
        trigger_super_alt_tab(true);
        trigger_super_alt_tab(true);
    }
    if(state->count > 3) {
        trigger_super_alt_tab(true);
    }
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_SUPER_ALT_TAB].step = dance_step(state);
    switch (dance_state[DNC_SUPER_ALT_TAB].step) {
        case SINGLE_TAP: trigger_super_alt_tab(true); break;
        case SINGLE_HOLD: register_code16(os_showallwins_key); break;
        case DOUBLE_TAP: trigger_super_alt_tab(true); trigger_super_alt_tab(true); break;
        case DOUBLE_SINGLE_TAP: trigger_super_alt_tab(true); trigger_super_alt_tab(true);
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_SUPER_ALT_TAB].step) {
        case SINGLE_TAP: trigger_super_alt_tab(false); break;
        case SINGLE_HOLD: unregister_code16(os_showallwins_key); break;
        case DOUBLE_TAP: trigger_super_alt_tab(false); break;
        case DOUBLE_SINGLE_TAP: trigger_super_alt_tab(false); break;
    }
    dance_state[DNC_SUPER_ALT_TAB].step = 0;
}


void curlyswap_finished(tap_dance_state_t *state, void *user_data);
void curlyswap_reset(tap_dance_state_t *state, void *user_data);

void curlyswap_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(state, KC_LCBR, KC_RCBR, DNC_CURLY);
}

void curlyswap_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(state, KC_LCBR, KC_RCBR, DNC_CURLY);
}


void squareswap_finished(tap_dance_state_t *state, void *user_data);
void squareswap_reset(tap_dance_state_t *state, void *user_data);

void squareswap_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(state, KC_LBRC, KC_RBRC, DNC_SQUARE);
}

void squareswap_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(state, KC_LBRC, KC_RBRC, DNC_SQUARE);
}


void dance_layerswap_finished(tap_dance_state_t *state, void *user_data);
void dance_layerswap_reset(tap_dance_state_t *state, void *user_data);

void dance_layerswap_finished(tap_dance_state_t *state, void *user_data) {
    int current_layer;

    dance_state[DNC_RTN_L0].step = dance_step(state);

    switch (dance_state[DNC_RTN_L0].step) {
        case SINGLE_TAP:
            if (layer_state_is(GAMING_LAYOUT)) {
                // noop
            } else if (get_highest_layer(layer_state) == UTIL_LAYOUT) {
                layer_off(UTIL_LAYOUT);
            } else {
                layer_on(UTIL_LAYOUT);
            }
            break;
        case SINGLE_HOLD:
            layer_on(UTIL_LAYOUT);
            break;
        case DOUBLE_TAP:
            current_layer = get_highest_layer(layer_state);
            if (current_layer == OS_WIN_LAYOUT) {
                layer_on(OS_MAC_LAYOUT);
            } else if (current_layer == OS_MAC_LAYOUT) {
                layer_off(OS_MAC_LAYOUT);
            } else {
                layer_state_set(1 << OS_WIN_LAYOUT | layer_state_is(OS_MAC_LAYOUT) << OS_MAC_LAYOUT );
            }
            break;
        #if CONSOLE_ENABLE
        case TRIPLE_TAP:
            uprintf("layer state: %d\n", layer_state);
            uprintf("mac state: %d\n", layer_state_is(OS_MAC_LAYOUT));
            uprintf("layer state: %d\n", 1 << OS_WIN_LAYOUT | layer_state_is(OS_MAC_LAYOUT) << OS_MAC_LAYOUT );
            break;
        #endif
    }
}


void dance_layerswap_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_RTN_L0].step) {
        #if CONSOLE_ENABLE
        case SINGLE_TAP:
            // noop
            break;
        #endif
        case SINGLE_HOLD:
            layer_off(UTIL_LAYOUT);
            break;
        case DOUBLE_TAP:
            // noop
            break;
    }
    dance_state[DNC_RTN_L0].step = 0;
}


void dance_bootloader_finished(tap_dance_state_t *state, void *user_data);

void dance_bootloader_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_BOOTLOADER].step = dance_step(state);
    switch (dance_state[DNC_BOOTLOADER].step) {
        case DOUBLE_HOLD: reset_keyboard(); break;
    }
}

void dance_bootloader_reset(tap_dance_state_t *state, void *user_data);

void dance_bootloader_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    dance_state[DNC_BOOTLOADER].step = 0;
}

// Keep this as a tap dance because builtins can't send modified keycodes
void dance_rh_fnswap_finished(tap_dance_state_t *state, void *user_data);
void dance_rh_fnswap_reset(tap_dance_state_t *state, void *user_data);

void dance_rh_fnswap_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_RH_FNSWAP].step = dance_step(state);
    switch (dance_state[DNC_RH_FNSWAP].step) {
        case SINGLE_TAP:
            register_code16(S(KC_SCLN));
            break;
        case SINGLE_HOLD: layer_on(FKEYS_LAYOUT); break;
    }
}

void dance_rh_fnswap_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_RH_FNSWAP].step) {
        case SINGLE_TAP:
            unregister_code16(S(KC_SCLN));
            break;
        case SINGLE_HOLD: layer_off(FKEYS_LAYOUT); break;
    }
    dance_state[DNC_RH_FNSWAP].step = 0;
}

void on_dance_backspace(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_BSPC, KC_BSPC, os_bksp_mod, DNC_BACKSPACE
    );
    }

void dance_backspace_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        state, KC_BSPC, KC_BSPC, os_bksp_mod, DNC_BACKSPACE
    );
    }

void dance_backspace_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        state, KC_BSPC, KC_BSPC, os_bksp_mod, DNC_BACKSPACE
    );
}


void on_dance_la(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_LEFT, KC_LEFT, os_bksp_mod, DNC_LEFT
    );
}

void dance_la_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        state, KC_LEFT, KC_LEFT, os_bksp_mod, DNC_LEFT
    );
}

void dance_la_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        state, KC_LEFT, KC_LEFT, os_bksp_mod, DNC_LEFT
    );
}

void on_dance_ra(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_RIGHT, KC_RIGHT, os_bksp_mod, DNC_RIGHT
    );
}

void dance_ra_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        state, KC_RIGHT, KC_RIGHT, os_bksp_mod, DNC_RIGHT
    );
}

void dance_ra_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        state, KC_RIGHT, KC_RIGHT, os_bksp_mod, DNC_RIGHT
    );
}


tap_dance_action_t tap_dance_actions[] = {
        [DNC_ESC_LS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DNC_FIND] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DNC_XCUT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DNC_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DNC_CPS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DNC_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DNC_SUPER_ALT_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DNC_RTN_L0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layerswap_finished, dance_layerswap_reset),
        [DNC_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, curlyswap_finished, curlyswap_reset),
        [DNC_SQUARE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, squareswap_finished, squareswap_reset),
        [DNC_BOOTLOADER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bootloader_finished, dance_bootloader_reset),
        [DNC_RH_FNSWAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rh_fnswap_finished, dance_rh_fnswap_reset),
        [DNC_BACKSPACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_backspace, dance_backspace_finished, dance_backspace_reset),
        [DNC_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_la, dance_la_finished, dance_la_reset),
        [DNC_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ra, dance_ra_finished, dance_ra_reset),
};
