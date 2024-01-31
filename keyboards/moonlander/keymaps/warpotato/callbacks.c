#ifndef KEYBOARD_HEADERS_INITIALIZED
#define KEYBOARD_HEADERS_INITIALIZED
#include QMK_KEYBOARD_H
#endif

#include "os_swap.h"
#include "layers_user.h"

uint32_t os_detection_callback(uint32_t trigger_time, void* cb_arg) {
  os_variant_t current_os = detected_host_os();
  if (current_os == OS_MACOS) {
    layer_on(OS_MAC_LAYOUT);
  }
  return 0;
}
