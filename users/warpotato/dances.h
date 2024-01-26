#pragma once

#define DANCES_INITIALIZED

#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#ifndef DANCES_TAPTYPES_INITIALIZED
#include "dances_taptypes.h"
#endif

uint8_t dance_step(tap_dance_state_t *state);
extern tap dance_state[MAX_COUNT_TAPDANCES];

void os_modkey_on_dance(tap_dance_state_t *state, uint16_t code);
void os_modkey_dance_finished(tap_dance_state_t *state, uint16_t code, int dance_index);
void os_modkey_dance_reset(tap_dance_state_t *state, uint16_t code, int dance_index);

void charswap_dance_finished(tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index);
void charswap_dance_reset(tap_dance_state_t *state, uint16_t base_code, uint16_t alt_code, int dance_index);
