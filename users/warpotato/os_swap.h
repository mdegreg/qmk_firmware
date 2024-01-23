
#define OS_SWAP_INITIALIZED

enum OS {
    OS_WINDOWS,
    OS_MAC,
};

extern int active_os;
extern int os_alt_tab_key;
extern int os_shortcut_key;
extern int os_showallwins_key;

void set_os(int os);
uint16_t os_make_command_letter_code(uint16_t code);
