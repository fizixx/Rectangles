// Rectangles

#include "named_rect.h"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>

// static
bool NamedRect::fromString(const std::string& str, NamedRect* rectOut) {
  NamedRect result;
  std::vector<std::string> parts;

  // Split the string into the parts separated by a comma.  We also skip
  // whitespace as we go.
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
        // Add the current string and clear it out for the next one.
        parts.push_back(current);
        current.clear();
      }
      continue;
    }

    // Nothing special, just add the character to the current string.
    current.push_back(ch);
  }

  // Add whatever is left in current to the parts.
  parts.push_back(current);

  // If we don't have at least 5 parts, we don't have a valid line.
  if (parts.size() < 5)
    return false;

  // Parse each part of the line into it's rectangle components.  We don't care
  // if the name is longer than one character, we just use the first one.
  result.name = parts[0][0];

  try {
    result.rect.left = std::stoi(parts[1]);
    result.rect.bottom = std::stoi(parts[1]);
    result.rect.right = std::stoi(parts[1]);
    result.rect.top = std::stoi(parts[1]);
  } catch (std::exception& e) {
    // If we can't convert any of the parts, then we assume it's not a valid
    // line, so we return false.
    return false;
  }

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
