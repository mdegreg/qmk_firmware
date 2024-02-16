

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
SRC += os_swap.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
OPT_DEFS += -DTAP_DANCE_ENABLE
SRC += dances.c
SRC += dances_user.c
endif
