//================================
// Tap dance configuration
//================================
#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "alttab.h"
#include "modifiers.h"
#include "os_swap.h"
#include "dances.h"
#include "dances_user.h"
#include "layers_user.h"

tap_dance_action_t tap_dance_actions[];
tap dance_state[MAX_COUNT_TAPDANCES];

/*
* Control tapdances
*
* Used to move around  between layers, trigger swaps, and other control
* flow type things.
*/

// for hopping to gaming layout
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

// allowing for OS swap and return to base layer from
// higher layers consistently
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

/*
* Utility tapdances
*
* These are generally used for general/productivity layers for
* making various actions and swaps easier to use, and generally
* being comfier.
*/

// Keep this as a tap dance because builtins can't send modified keycodes
// For allowing send of a handy lil : while also allowing for swap to
// symbol layer
void on_dance_rh(tap_dance_state_t *state, void *user_data);
void dance_rh_fnswap_finished(tap_dance_state_t *state, void *user_data);
void dance_rh_fnswap_reset(tap_dance_state_t *state, void *user_data);

void on_dance_rh(tap_dance_state_t* state, void* user_data) {
    if(state->count == 3) {
        tap_code16(S(KC_SCLN));
        tap_code16(S(KC_SCLN));
        tap_code16(S(KC_SCLN));
    }
    if(state->count > 3) {
        tap_code16(S(KC_SCLN));
    }
}

void dance_rh_fnswap_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_RH_FNSWAP].step = dance_step(state);
    switch (dance_state[DNC_RH_FNSWAP].step) {
        case SINGLE_TAP:
            register_code16(S(KC_SCLN));
            break;
        case SINGLE_HOLD: layer_on(FKEYS_LAYOUT); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            tap_code16(S(KC_SCLN));
            register_code16(S(KC_SCLN));
    }
}

void dance_rh_fnswap_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_RH_FNSWAP].step) {
        case SINGLE_TAP:
            unregister_code16(S(KC_SCLN));
            break;
        case SINGLE_HOLD: layer_off(FKEYS_LAYOUT); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code16(S(KC_SCLN));
    }
    dance_state[DNC_RH_FNSWAP].step = 0;
}

void on_dance_lh(tap_dance_state_t *state, void *user_data);
void dance_lh_fnswap_finished(tap_dance_state_t *state, void *user_data);
void dance_lh_fnswap_reset(tap_dance_state_t *state, void *user_data);


void on_dance_lh(tap_dance_state_t* state, void* user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}
void dance_lh_fnswap_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_LH_FNSWAP].step = dance_step(state);
    switch (dance_state[DNC_LH_FNSWAP].step) {
        case SINGLE_TAP:
            register_code16(KC_TAB);
            break;
        case SINGLE_HOLD: layer_on(FKEYS_LAYOUT); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_TAB);
            register_code16(KC_TAB);
    }
}

void dance_lh_fnswap_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[DNC_LH_FNSWAP].step) {
        case SINGLE_TAP:
            unregister_code16(KC_TAB);
            break;
        case SINGLE_HOLD: layer_off(FKEYS_LAYOUT); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_TAB);
    }
    dance_state[DNC_LH_FNSWAP].step = 0;
}

// keyboard shortcut triggers on hold
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_F);
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(&(dance_state[DNC_FIND]), state, KC_F);
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(&(dance_state[DNC_FIND]), state, KC_F);
}

void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_X);
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(&(dance_state[DNC_XCUT]), state, KC_X);
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(&(dance_state[DNC_XCUT]), state, KC_X);
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_C);
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(&(dance_state[DNC_COPY]), state, KC_C);
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(&(dance_state[DNC_COPY]), state, KC_C);
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    os_modkey_on_dance(state, KC_V);
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_finished(&(dance_state[DNC_CPS]), state, KC_V);
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    os_modkey_dance_reset(&(dance_state[DNC_CPS]), state, KC_V);
}

void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

// because alt tab is effortful, and i needed to figure out
// how more complex behaviors work within qmk
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
    charswap_dance_finished(&(dance_state[DNC_CURLY]), state, KC_LCBR, KC_RCBR);
}

void curlyswap_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(&(dance_state[DNC_CURLY]), state, KC_LCBR, KC_RCBR);
}


void squareswap_finished(tap_dance_state_t *state, void *user_data);
void squareswap_reset(tap_dance_state_t *state, void *user_data);

void squareswap_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(&(dance_state[DNC_SQUARE]), state, KC_LBRC, KC_RBRC);
}

void squareswap_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(&(dance_state[DNC_SQUARE]), state, KC_LBRC, KC_RBRC);
}

// reduce accidental bootloader triggers while having it more accessible
// without a paperclip
void dance_bootloader_finished(tap_dance_state_t *state, void *user_data);
void dance_bootloader_reset(tap_dance_state_t *state, void *user_data);

void dance_bootloader_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[DNC_BOOTLOADER].step = dance_step(state);
    switch (dance_state[DNC_BOOTLOADER].step) {
        case DOUBLE_HOLD: reset_keyboard(); break;
    }
}

void dance_bootloader_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    dance_state[DNC_BOOTLOADER].step = 0;
}

// a few navigation utils for editing and working with
// CLI commands

// delete a whole word on hold
void on_dance_backspace(tap_dance_state_t* state, void* user_data) {
    on_mod_charswap_dance(
        state, KC_BSPC, KC_BSPC, os_bksp_mod
    );
}

void dance_backspace_finished(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_finished(
        &(dance_state[DNC_BACKSPACE]), state, KC_BSPC, KC_BSPC, os_bksp_mod
    );
}

void dance_backspace_reset(tap_dance_state_t* state, void* user_data) {
    mod_charswap_dance_reset(
        &(dance_state[DNC_BACKSPACE]), state, KC_BSPC, KC_BSPC, os_bksp_mod
    );
}

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

void on_dance_space(tap_dance_state_t *state, void *user_data);
void dance_space_finished(tap_dance_state_t *state, void *user_data);
void dance_space_reset(tap_dance_state_t *state, void *user_data);

void on_dance_space(tap_dance_state_t *state, void *user_data) {
    on_charswap_dance(state, KC_SPACE, KC_UNDS);
}

void dance_space_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(&(dance_state[DNC_SPACE]), state, KC_SPACE, KC_UNDS);
}

void dance_space_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(&(dance_state[DNC_SPACE]), state, KC_SPACE, KC_UNDS);

void on_dance_brc(tap_dance_state_t *state, void *user_data);
void dance_brc_finished(tap_dance_state_t *state, void *user_data);
void dance_brc_reset(tap_dance_state_t *state, void *user_data);

void on_dance_brc(tap_dance_state_t *state, void *user_data) {
    on_charswap_dance(state, KC_LBRC, KC_RBRC);
}

void dance_brc_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(&(dance_state[DNC_BRC]), state, KC_LBRC, KC_RBRC);
}

void dance_brc_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(&(dance_state[DNC_BRC]), state, KC_LBRC, KC_RBRC);
}

void on_dance_paren(tap_dance_state_t *state, void *user_data);
void dance_paren_finished(tap_dance_state_t *state, void *user_data);
void dance_paren_reset(tap_dance_state_t *state, void *user_data);

void on_dance_paren(tap_dance_state_t *state, void *user_data) {
    on_charswap_dance(state, S(KC_9), S(KC_0));
}

void dance_paren_finished(tap_dance_state_t *state, void *user_data) {
    charswap_dance_finished(&(dance_state[DNC_PAREN]), state, S(KC_9), S(KC_0));
}

void dance_paren_reset(tap_dance_state_t *state, void *user_data) {
    charswap_dance_reset(&(dance_state[DNC_PAREN]), state, S(KC_9), S(KC_0));
}

tap_dance_action_t tap_dance_actions[] = {
        [DNC_ESC_LS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DNC_FIND] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DNC_XCUT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DNC_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DNC_CPS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DNC_SUPER_ALT_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DNC_RTN_L0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layerswap_finished, dance_layerswap_reset),
        [DNC_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, curlyswap_finished, curlyswap_reset),
        [DNC_SQUARE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, squareswap_finished, squareswap_reset),
        [DNC_BOOTLOADER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bootloader_finished, dance_bootloader_reset),
        [DNC_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_space, dance_space_finished, dance_space_reset),
        [DNC_RH_FNSWAP] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_rh, dance_rh_fnswap_finished, dance_rh_fnswap_reset),
        [DNC_LH_FNSWAP] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_lh, dance_lh_fnswap_finished, dance_lh_fnswap_reset),
        [DNC_BACKSPACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_backspace, dance_backspace_finished, dance_backspace_reset),
        [DNC_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_la, dance_la_finished, dance_la_reset),
        [DNC_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ra, dance_ra_finished, dance_ra_reset),
        [DNC_BRC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ra, dance_ra_finished, dance_ra_reset),
};
