// Rectangles

#include "named_rect.h"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>

bool NamedRect::fromString(const std::string& str, NamedRect* rectOut) {
  NamedRect result;
  std::vector<std::string> parts;

  size_t i = 0;
  const size_t strLen = str.length();
  std::string current;
  while (i < strLen) {
    const char ch = str[i++];

    // Skip any whitespace.
    if (std::isspace(ch))
      continue;

    if (ch == ',') {
      if (!current.empty()) {
        parts.push_back(current);
        current.clear();
      }
      continue;
    }

    current.push_back(ch);
  }

  // Add whatever is left in current to the parts.
  parts.push_back(current);

  // If we don't have at least 5 parts, we don't have a valid line.
  if (parts.size() < 5)
    return false;

  // Parse each part of the line into it's rectangle components.
  result.name = parts[0][0];

  result.rect.left = atoi(parts[1].c_str());
  result.rect.bottom = atoi(parts[2].c_str());
  result.rect.right = atoi(parts[3].c_str());
  result.rect.top = atoi(parts[4].c_str());

  *rectOut = result;

  return true;
}

bool readRectanglesFromFile(const std::string& filename,
    std::vector<NamedRect>* rectanglesOut) {
  assert(rectanglesOut);

  std::ifstream inFile(filename, std::ios::in);
  if (!inFile.is_open())
    return false;

  std::string line;
  NamedRect rect;
  while (!inFile.eof()) {
    std::getline(inFile, line);
    if (!line.empty() && NamedRect::fromString(line, &rect))
      rectanglesOut->push_back(rect);
  }

  return true;
}
