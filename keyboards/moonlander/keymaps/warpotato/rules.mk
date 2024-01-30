# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
ORYX_ENABLE = no
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
OS_DETECTION_ENABLE = yes
MAGIC_ENABLE = no

SRC = matrix.c
SRC += alttab.c
SRC += modifiers.c
SRC += os_swap.c
SRC += dances.c

ifeq ($(strip $(ORYX_ENABLE)), yes)
    RAW_ENABLE := yes
    SRC += oryx.c
	OPT_DEFS += DORYX_CONFIGURATOR
	OPT_DEFS += -DORYX_ENABLE
endif
