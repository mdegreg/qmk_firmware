# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

# debug defs
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no

# feature defs
KEY_OVERRIDE_ENABLE = no
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
ORYX_ENABLE = no
TAP_DANCE_ENABLE = yes

# firmware size optimizations
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no

# custom behavior
SUPER_ALT_TAB_ENABLE = yes
OS_SWAP_CMD_KEY_ENABLE = yes

SRC = matrix.c
SRC += modifiers.c
