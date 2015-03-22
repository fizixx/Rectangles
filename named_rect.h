// Rectangles

#ifndef NAMED_RECT_H_
#define NAMED_RECT_H_

#include <ostream>
#include <string>
#include <vector>

#include "rect.h"

struct NamedRect {
  char name;
  Rect rect;

  static bool fromString(const std::string& str, NamedRect* rectOut);

  NamedRect()
      : name(0) {
  }

  friend std::ostream& operator<<(std::ostream& os,
      const NamedRect& namedRect) {
    os << namedRect.name << " - " << namedRect.rect;
    return os;
  }
};

// Read a list of rectangles from the file with the given name.  The rectangles
// will be added to rectanglesOut.
bool readRectanglesFromFile(const std::string& filename,
    std::vector<NamedRect>* rectanglesOut);

#endif  // NAMED_RECT_H_
