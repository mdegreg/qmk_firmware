#pragma once

enum super_alt_tab_os {
    SAT_WIN,
    SAT_MAC
};

extern int SUPER_ALT_TAB_TIMEOUT_MS;
extern bool is_alt_tab_active;
extern int alt_tab_init_key;
extern int alt_tab_timer;

void set_super_alt_tab_init_key(int key);
void unset_super_alt_tab_init_key(void);
void trigger_super_alt_tab(bool pressed);
void timeout_super_alt_tab(void);
