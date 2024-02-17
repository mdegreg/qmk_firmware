#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "dances_taptypes.h"
#include "dances.h"

enum {
    CTRL_TAB_IDLE = 0,
    CTRL_TAB_ACTIVE,
    CTRL_TAB_ACTIVE_REVERSED,
};

const int SUPER_CTRL_TAB_TIMEOUT_MS = 1000;
const int ctrl_tab_default_value = -1;
int ctrl_tab_state = CTRL_TAB_IDLE;
int is_ctrl_tab;
int ctrl_tab_timer = 0;

void trigger_super_ctrl_tab(bool reverse) {
    if (!ctrl_tab_state) {
      register_code(KC_LCTL);
      if (reverse) {
        register_code(KC_LSFT);
        ctrl_tab_state = CTRL_TAB_ACTIVE_REVERSED;
      } else {
        ctrl_tab_state = CTRL_TAB_ACTIVE;
      }
    } else if ((ctrl_tab_state == CTRL_TAB_ACTIVE_REVERSED) & !reverse) {
        unregister_code(KC_LSFT);
        ctrl_tab_state = CTRL_TAB_ACTIVE;
    } else if ((ctrl_tab_state == CTRL_TAB_ACTIVE) & reverse) {
        register_code(KC_LSFT);
        ctrl_tab_state = CTRL_TAB_ACTIVE_REVERSED;
    }
    ctrl_tab_timer = timer_read();
    tap_code(KC_TAB);
}

void timeout_super_ctrl_tab(void) {
  if (ctrl_tab_state) {
    if (timer_elapsed(ctrl_tab_timer) > SUPER_CTRL_TAB_TIMEOUT_MS) {
      unregister_code(KC_LCTL);
      if (ctrl_tab_state == CTRL_TAB_ACTIVE_REVERSED) {
        unregister_code(KC_LSFT);
      }
      ctrl_tab_state = CTRL_TAB_IDLE;
    }
  }
}
