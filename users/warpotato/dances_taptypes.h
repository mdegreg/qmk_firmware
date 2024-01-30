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

