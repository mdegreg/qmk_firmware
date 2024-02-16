#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "os_swap.h"
#include "dances_taptypes.h"
#include "dances.h"

const int SUPER_ALT_TAB_TIMEOUT_MS = 1000;
const int alt_tab_default_value = -1;
int is_alt_tab_active = false;
int alt_tab_timer = 0;
int alt_tab_init_key = -1;

void set_super_alt_tab_init_key(int key) {
  // Set the key used to start an alt-tab sequence
  alt_tab_init_key = key;
}

void unset_super_alt_tab_init_key(void) {
  // For clarity in the code, we don't want to use -1 as a special value
  alt_tab_init_key = -1;
}

void trigger_super_alt_tab(bool pressed) {
    // Trigger the single key alt-tab logic
    if (alt_tab_init_key == -1) {
      // NOOP if the init key is not set
      return;
    } else if (pressed) {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(alt_tab_init_key);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
}

void timeout_super_alt_tab(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > SUPER_ALT_TAB_TIMEOUT_MS) {
      unregister_code(alt_tab_init_key);
      is_alt_tab_active = false;
    }
  }
}
// because alt tab is effortful, and i needed to figure out
// how more complex behaviors work within qmk
void alt_tab_tap(tap_dance_state_t *state) {
    if(state->count == 3) {
        trigger_super_alt_tab(true);
        trigger_super_alt_tab(true);
        trigger_super_alt_tab(true);
    }
    if(state->count > 3) {
        trigger_super_alt_tab(true);
    }
}

void alt_tab_finished(tap *tap_state, tap_dance_state_t *state) {
    tap_state->step = dance_step(state);
    switch (tap_state->step) {
        case SINGLE_TAP: trigger_super_alt_tab(true); break;
        #ifdef OS_SWAP_CMD_KEY_ENABLE
        case SINGLE_HOLD: register_code16(os_showallwins_key); break;
        #endif
        case DOUBLE_TAP: trigger_super_alt_tab(true); trigger_super_alt_tab(true); break;
        case DOUBLE_SINGLE_TAP: trigger_super_alt_tab(true); trigger_super_alt_tab(true);
    }
}

void alt_tab_reset(tap *tap_state, tap_dance_state_t *state) {
    wait_ms(10);
    switch (tap_state->step) {
        case SINGLE_TAP: trigger_super_alt_tab(false); break;
        #ifdef OS_SWAP_CMD_KEY_ENABLE
        case SINGLE_HOLD: unregister_code16(os_showallwins_key); break;
        #endif
        case DOUBLE_TAP: trigger_super_alt_tab(false); break;
        case DOUBLE_SINGLE_TAP: trigger_super_alt_tab(false); break;
    }
    tap_state->step = 0;
}
