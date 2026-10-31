#include "../uid_match.h"
#include <assert.h>

int main() {
  const uint8_t allowed[7] = {1, 2, 3, 4, 5, 6, 7};
  const uint8_t exact[7] = {1, 2, 3, 4, 5, 6, 7};
  const uint8_t prefix[4] = {1, 2, 3, 4};
  const uint8_t longer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const uint8_t different[7] = {1, 2, 3, 4, 5, 6, 8};
  assert(uidMatches(exact, sizeof(exact), allowed));
  assert(!uidMatches(prefix, sizeof(prefix), allowed));
  assert(!uidMatches(longer, sizeof(longer), allowed));
  assert(!uidMatches(different, sizeof(different), allowed));
  assert(!uidMatches(nullptr, 0, allowed));
  assert(!uidMatches(exact, 0, allowed));
  assert(!uidMatches(nullptr, sizeof(allowed), allowed));
}
