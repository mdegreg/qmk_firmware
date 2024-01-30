#pragma once

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    
    # if CONSOLE_ENABLE
    TRIPLE_TAP,
    TRIPLE_HOLD,
    TRIPLE_SINGLE_TAP,
    # endif
    MORE_TAPS
};

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum tap_dance_codes {
  DNC_ESC_LS,
  DNC_FIND,
  DNC_XCUT,
  DNC_COPY,
  DNC_CPS,
  DNC_SPC,
  DNC_SUPER_ALT_TAB,
  DNC_RTN_L0,
  DNC_CURLY,
  DNC_SQUARE,
  DNC_BOOTLOADER,
  DNC_RH_FNSWAP,
  DNC_BACKSPACE,
  DNC_LEFT,
  DNC_RIGHT,

  DNC_SADHOP,
  /*
  ** Do not change or move from bottom of enum. **

  An enum by default has the value 0 for the 
  first value, incrementing by 1 each time.
  
  Leaving this as is will take advantage of that,
  as the last item will be equal to the length of
  the array of items above, e.g. the bottom value
  will be the number of items excluding itself.

  We use the last item here to indicate dynamically
  how many tap dance functions we support within this keymap.
  */ 
  MAX_COUNT_TAPDANCES 
};
