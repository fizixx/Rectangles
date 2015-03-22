// Rectangles

#include <cassert>
#include <iostream>

#include "rect.h"

void testContains() {
  std::cout << "testContains: ";
  assert(Rect(1, 1, 4, 4).contains(Rect(2, 2, 3, 3)));
  assert(!Rect(1, 1, 4, 4).contains(Rect(1, 1, 5, 5)));
  std::cout << "OK" << std::endl;
}

void testOverlaps() {
  std::cout << "testOverlaps: ";
  assert(Rect(1, 1, 4, 4).overlaps(Rect(1, 1, 5, 5)));
  assert(Rect(1, 1, 4, 4).overlaps(Rect(2, 2, 3, 3)));
  assert(!Rect(1, 1, 4, 4).overlaps(Rect(5, 1, 6, 4)));
  std::cout << "OK" << std::endl;
}

int main() {
  std::cout << "rect_test" << std::endl;

  testContains();
  testOverlaps();

  return 0;
}
