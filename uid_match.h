#pragma once

#include <stddef.h>
#include <stdint.h>

// Compare a complete UID, never a prefix. Check the length before accessing
// either buffer so 4-, 7- and 10-byte cards cannot overrun stored credentials.
template <size_t ExpectedSize>
bool uidMatches(const uint8_t* actual, size_t actualSize,
                const uint8_t (&expected)[ExpectedSize]) {
  if (actual == nullptr || actualSize != ExpectedSize) {
    return false;
  }
  for (size_t i = 0; i < ExpectedSize; ++i) {
    if (actual[i] != expected[i]) {
      return false;
    }
  }
  return true;
}
