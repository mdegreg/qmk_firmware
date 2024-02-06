#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#ifdef SUPER_ALT_TAB_ENABLE
#include "alttab.h"
#endif

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#include "quantum_keycodes.h"
#include "os_detection.h"

/*
Note that there is a builtin optional header that will declare functions for this

https://docs.qmk.fm/#/feature_os_detection
*/

int active_os = OS_WINDOWS;
int os_alt_tab_key = KC_LALT;
int os_showallwins_key = LGUI(KC_TAB);
uint16_t os_bksp_mod = QK_LCTL;

void set_os(int os){
    switch(os){
        case OS_WINDOWS:
            active_os = OS_WINDOWS;
            os_alt_tab_key = KC_LALT;
            os_showallwins_key = LGUI(KC_TAB);
            os_bksp_mod = QK_LCTL;
            break;
        case OS_MACOS:
            active_os = OS_MACOS;
            os_alt_tab_key = KC_LGUI;
            os_showallwins_key = LCTL(KC_UP);
            os_bksp_mod = QK_LALT;
            break;
    }
    
#ifdef SUPER_ALT_TAB_ENABLE
    set_super_alt_tab_init_key(os_alt_tab_key);
#endif
}

#ifdef OS_SWAP_CMD_KEY_ENABLE
uint16_t os_make_command_letter_code(uint16_t code){
    uint16_t return_code;
    if (active_os == OS_WINDOWS){
        return_code = LCTL(code);
    } else {
        return_code = LGUI(code);
    }
#ifdef CONSOLE_ENABLE
    uprintf("OS: %d | code 0x%04X\n", active_os, return_code);
#endif
    return return_code;
}
#endif
