#pragma once

#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif
#include "dances_user.h"
#include "layers_user.h"
#include "custom_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
Push rollers start at top left
*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                KC_7,     KC_8,    KC_9,    TD(DNC_MINUS),     KC_MUTE,
                KC_4,     KC_5,    KC_6,    TD(DNC_PLUS),      _______,
                KC_1,     KC_2,    KC_3,    _______,          _______,
                KC_0,     KC_DOT,  KC_BSPC,   KC_ENT
            ),
    [NAVARROW] = LAYOUT(
                KC_HOME,     _______,    KC_PGUP,    TD(DNC_SUPER_ALT_TAB),     KC_MUTE,
                S_CTRL_TAB_R,     _______,    S_CTRL_TAB,    KC_BSPC,      _______,
                KC_END,     KC_UP,    KC_PGDN,    KC_ENT,          _______,
                KC_LEFT,     KC_DOWN,  KC_RIGHT,   _______
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
    /*  Row:    0        1        2        3        4       */
    [SONAR] = LAYOUT(
                A(KC_BSLS), A(KC_KP_SLASH), A(KC_KP_ASTERISK), _______, A(KC_KP_0),
                A(KC_KP_3), A(KC_KP_9), A(KC_KP_6), _______, _______,
                A(KC_KP_2), A(KC_KP_8), A(KC_KP_5), _______, _______,
                A(KC_KP_1), A(KC_KP_7), A(KC_KP_4), _______
            ),
};
