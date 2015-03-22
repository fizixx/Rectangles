// Rectangles

#ifndef RECT_H_
#define RECT_H_

#include <iostream>

struct Rect {
  int left, bottom, right, top;

  Rect()
      : left(0), bottom(0), right(0), top(0) {
  }

  Rect(int left, int bottom, int right, int top)
      : left(left), bottom(bottom), right(right), top(top) {
  }

  // Returns true if this rectangle completely contains the given rectangle.
  bool contains(const Rect& other) const {
    return (left <= other.left && right >= other.right && top >= other.top
        && bottom <= other.bottom);
  }

  // Returns true if this rectangle overlaps the given rectangle.
  bool overlaps(const Rect& other) const {
    return (left < other.right && right > other.left && top > other.bottom
        && bottom < other.top);
  }

  // Returns true if this rectangle touches the given rectangle.
  bool touches(const Rect& other) const {
    return (left == other.right || right == other.left || top == other.bottom
        || bottom == other.top);
  }

  friend std::ostream& operator<<(std::ostream& os, const Rect& rect) {
    os << "(" << rect.left << ", " << rect.bottom << ", " << rect.right << ", "
        << rect.top << ")";
    return os;
  }

};

#endif  // RECT_H_
