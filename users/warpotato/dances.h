#pragma once

#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "dances_taptypes.h"

uint8_t dance_step(tap_dance_state_t *state);

void os_modkey_on_dance(tap_dance_state_t *state, uint16_t code);
void os_modkey_dance_finished(tap *tap_state, tap_dance_state_t *state, uint16_t code, int dance_index);
void os_modkey_dance_reset(tap *tap_state, tap_dance_state_t *state, uint16_t code, int dance_index);

void on_charswap_dance(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, int dance_index);
void charswap_dance_finished(tap *tap_state, tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index);
void charswap_dance_reset(tap *tap_state, tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index);

void on_mod_charswap_dance(tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index);
void mod_charswap_dance_finished(tap *tap_state, tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index);
void mod_charswap_dance_reset(tap *tap_state, tap_dance_state_t* state, uint16_t base_code, uint16_t alt_code, uint16_t alt_mod, int dance_index);
