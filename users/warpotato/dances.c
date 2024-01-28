#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#ifndef OS_SWAP_INITIALIZED
#include "os_swap.h"
#endif

#ifndef DANCES_TAPTYPES_INITIALIZED
#include "dances_taptypes.h"
#endif

tap dance_state[MAX_COUNT_TAPDANCES];

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    # if CONSOLE_ENABLE
    } else if (state->count == 3) {
        if (state->interrupted) return TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TRIPLE_HOLD;
        else return TRIPLE_TAP;
    # endif
    }
    return MORE_TAPS;
}

/*
Note that modkey and charswap dances fire their hold action once, rather than holding
when the key is held. This precludes using keys bound to this dance type
from spamming their hold action value.
*/

void os_modkey_on_dance(tap_dance_state_t *state, uint16_t code) {
    if(state->count == 3) {
        tap_code16(code);
        tap_code16(code);
        tap_code16(code);

#if CONSOLE_ENABLE
    uprintf("Fired triple tap: %u\n", code);
#endif
    }
    if(state->count > 3) {
        tap_code16(code);
    }

#if CONSOLE_ENABLE
    uprintf("Fired longhold tap: %u\n", code);
#endif
}

void os_modkey_dance_finished(tap_dance_state_t *state, uint16_t code, int dance_index) {

    #if CONSOLE_ENABLE
    uprintf("Received code: %u\n", code);
    #endif
    dance_state[dance_index].step = dance_step(state);
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP:
            #if CONSOLE_ENABLE
            uprintf("Fired SINGLE_TAP: %u\n", code);
            #endif
            tap_code16(code);
            break;
        case SINGLE_HOLD:
            #if CONSOLE_ENABLE
            uprintf("Fired SINGLE_HOLD: %u\n", code);
            #endif
            tap_code16(os_make_command_letter_code(code));
            break;
        case DOUBLE_TAP:
            #if CONSOLE_ENABLE
            uprintf("Fired DOUBLE_TAP: %u\n", os_make_command_letter_code(code));
            #endif
        case DOUBLE_SINGLE_TAP:
#if CONSOLE_ENABLE
            uprintf("Fired DOUBLE_SINGLE_TAP: %u\n", code);
#endif
            tap_code16(code);
            register_code16(code);
    }
}

void os_modkey_dance_reset(tap_dance_state_t *state, uint16_t code, int dance_index) {
    wait_ms(10);
    #if CONSOLE_ENABLE
    uprintf("Received code: %u\n", code);
    #endif
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP:
            #if CONSOLE_ENABLE
            uprintf("Fired SINGLE_TAP: %u\n", code);
            #endif
            break;
        case SINGLE_HOLD:
        #if CONSOLE_ENABLE
            uprintf("Fired SINGLE_HOLD: %u\n", os_make_command_letter_code(code));
        #endif
            break;
        case DOUBLE_TAP:
            #if CONSOLE_ENABLE
            uprintf("Fired DOUBLE_TAP: %u\n", code);
            #endif
        case DOUBLE_SINGLE_TAP:
            #if CONSOLE_ENABLE
            uprintf("Fired DOUBLE_SINGLE_TAP: %u\n", code);
            #endif
            unregister_code16(code);
            break;
    }
    dance_state[dance_index].step = 0;
}

void on_charswap_dance(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, int dance_index) {
    if(state->count == 3) {
        tap_code16(base_code);
        tap_code16(base_code);
        tap_code16(base_code);
    }
    if(state->count > 3) {
        tap_code16(base_code);
    }
}

void charswap_dance_finished(tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index) {
    dance_state[dance_index].step = dance_step(state);
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP: register_code16(base_code); break;
        case SINGLE_HOLD: tap_code16(alt_code); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP: tap_code16(base_code); register_code16(base_code);
    }
}

void charswap_dance_reset(tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index) {
    wait_ms(10);
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP: unregister_code16(base_code); break;
        case SINGLE_HOLD: break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP: unregister_code16(base_code);
    }
    dance_state[dance_index].step = 0;
}

void on_mod_charswap_dance(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index) {
    if(state->count == 3) {
        tap_code16(base_code);
        tap_code16(base_code);
        tap_code16(base_code);
    }
    if(state->count > 3) {
        tap_code16(base_code);
    }
}

void mod_charswap_dance_finished(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index) {
    dance_state[dance_index].step = dance_step(state);
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP: register_code16(base_code); break;
        case SINGLE_HOLD: tap_code16(alt_mod | alt_code); break;
        case DOUBLE_TAP: break;
        case DOUBLE_SINGLE_TAP: tap_code16(base_code); register_code16(base_code);
    }
}

void mod_charswap_dance_reset(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index) {
    wait_ms(10);
    switch (dance_state[dance_index].step) {
        case SINGLE_TAP: unregister_code16(base_code); break;
        case SINGLE_HOLD: break;
        case DOUBLE_TAP: break;
        case DOUBLE_SINGLE_TAP: unregister_code16(base_code);
    }
    dance_state[dance_index].step = 0;
}
