//================================
// Tap dance configuration
//================================
#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "dances.h"
#include "dances_user.h"
#include "os_swap.h"
#include "alttab.h"

tap_dance_action_t tap_dance_actions[];
tap dance_state[MAX_COUNT_TAPDANCES];

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

void on_dance_plus(tap_dance_state_t* state, void* user_data) {
    on_charswap_dance(
        state, KC_KP_PLUS, KC_KP_ASTERISK
    );
}

void dance_plus_finished(tap_dance_state_t* state, void* user_data) {
    charswap_dance_finished(
        &(dance_state[DNC_PLUS]), state, KC_KP_PLUS, KC_KP_ASTERISK
    );
}

void dance_plus_reset(tap_dance_state_t* state, void* user_data) {
    charswap_dance_reset(
        &(dance_state[DNC_PLUS]), state, KC_KP_PLUS, KC_KP_ASTERISK
    );
}

void on_dance_minus(tap_dance_state_t* state, void* user_data) {
    on_charswap_dance(
        state, KC_KP_MINUS, KC_KP_SLASH
    );
}

void dance_minus_finished(tap_dance_state_t* state, void* user_data) {
    charswap_dance_finished(
        &(dance_state[DNC_MINUS]), state, KC_KP_MINUS, KC_KP_SLASH
    );
}

void dance_minus_reset(tap_dance_state_t* state, void* user_data) {
    charswap_dance_reset(
        &(dance_state[DNC_MINUS]), state, KC_KP_MINUS, KC_KP_SLASH
    );
}

void super_alt_tab_finished(tap_dance_state_t *state, void *user_data) {
    alt_tab_finished(&(dance_state[DNC_SUPER_ALT_TAB]), state);
}

void super_alt_tab_reset(tap_dance_state_t *state, void *user_data) {
    alt_tab_reset(&(dance_state[DNC_SUPER_ALT_TAB]), state);
}

tap_dance_action_t tap_dance_actions[] = {
        [DNC_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_la, dance_la_finished, dance_la_reset),
        [DNC_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ra, dance_ra_finished, dance_ra_reset),
        [DNC_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_plus, dance_plus_finished, dance_plus_reset),
        [DNC_MINUS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_minus, dance_minus_finished, dance_minus_reset),
        [DNC_SUPER_ALT_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, super_alt_tab_finished, super_alt_tab_reset),
};
