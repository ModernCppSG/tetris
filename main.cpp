#include "gtest/gtest.h"
#include "refframes.h"

int main() {
  return RUN_ALL_TESTS();
  ReferenceFrame local(5, 21);  // Block starts at MIDLE-TOP of playing field
  ReferenceFrame GLOBAL(0, 0);
  ReferenceFrame PRINTING(0, 20);  // TODO(aocci): flip the printing Frame down
}
