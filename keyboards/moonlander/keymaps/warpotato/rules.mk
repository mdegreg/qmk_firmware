# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

# debug defs
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no

# feature defs
ORYX_ENABLE = no
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# firmware size optimizations
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no

# custom behavior
SUPER_ALT_TAB_ENABLE = yes
OS_SWAP_CMD_KEY_ENABLE = yes

SRC = matrix.c
SRC += modifiers.c
SRC += os_swap.c
SRC += dances.c
SRC += dances_user.c
SRC += callbacks.c

ifeq ($(strip $(ORYX_ENABLE)), yes)
    RAW_ENABLE := yes
    SRC += oryx.c
	OPT_DEFS += DORYX_CONFIGURATOR
	OPT_DEFS += -DORYX_ENABLE
endif

ifeq ($(strip $(SUPER_ALT_TAB_ENABLE)), yes)
	SRC += alttab.c
    OPT_DEFS += -DSUPER_ALT_TAB_ENABLE
endif

ifeq ($(strip $(OS_SWAP_CMD_KEY_ENABLE)), yes)
    OPT_DEFS += -DOS_SWAP_CMD_KEY_ENABLE
endif
