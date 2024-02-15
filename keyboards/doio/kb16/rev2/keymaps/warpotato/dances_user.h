#pragma once

enum tap_dance_codes {
  DNC_LEFT,
  DNC_RIGHT,
  DNC_PLUS,
  DNC_MINUS,
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
  MAX_COUNT_TAPDANCES,
};

extern tap_dance_action_t tap_dance_actions[];
tap dance_state[MAX_COUNT_TAPDANCES];
