#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

const int moonlander_capslock_index = 2;

bool is_caps_lock_on(void) {
    led_t led_state = host_keyboard_led_state();
    return led_state.caps_lock;
}

bool is_num_lock_on(void) {
    led_t led_state = host_keyboard_led_state();
    return led_state.num_lock;
}
