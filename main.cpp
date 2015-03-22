// Rectangles

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "named_rect.h"

struct Results {
  std::vector<char> overlaps;
  std::vector<char> contains;
  std::vector<char> containedBy;
  std::vector<char> touches;
};

// A structure to store our results in.
using ResultsType = std::unordered_map<char, Results>;

// Get the corresponding Result object for the given rectangle name.
Results* getResults(ResultsType* results, char name) {
  bool inserted = false;
  auto it = results->find(name);
  if (it == std::end(*results))
    std::tie(it, inserted) = results->insert(std::make_pair(name, Results()));

  return &it->second;
}

// Given a list of rectangle names, print them out in a comma separated line.
void printNames(std::ostream& os, const std::vector<char>& names) {
  if (names.empty()) {
    os << '0';
  } else {
    const size_t size = names.size();
    for (size_t i = 0; i < size; ++i) {
      os << names[i];
      if (i < size - 1)
        os << ',';
    }
  }
  os << std::endl;
}

void printResults(std::ostream& os, const ResultsType& results) {
  for (const auto& it : results) {
    os << it.first << std::endl;
    printNames(os, it.second.overlaps);
    printNames(os, it.second.contains);
    printNames(os, it.second.containedBy);
    printNames(os, it.second.touches);
    os << std::endl;
  }
}

int main(int argc, char* argv[]) {
  std::string inFilename, outFilename;

  if (argc < 2) {
    std::cout << "USAGE: " << argv[0] << " <input file> [<output file>]"
        << std::endl;
    return 1;
  }

  if (argc >= 2)
    inFilename = std::string(argv[1]);

  if (argc >= 3)
    outFilename = std::string(argv[2]);

  std::vector<NamedRect> rectangles;

  // Read the rectangles in the file into our list of rectangles.
  std::cout << "Loading rectangles from file: " << inFilename << std::endl;
  if (!readRectanglesFromFile(inFilename, &rectangles)) {
    std::cerr << "Could not open input file: " << inFilename << std::endl;
    return 1;
  }

#if 0
  for (const auto& rect : rectangles)
  std::cout << "Rect: " << rect << std::endl;
#endif  // 0

  std::cout << "Calculating results..." << std::endl;

  ResultsType results;
  for (const auto& first : rectangles) {
    Results* r = getResults(&results, first.name);

    for (const auto& second : rectangles) {
      if (first.rect.overlaps(second.rect))
        r->overlaps.push_back(second.name);
      if (first.rect.contains(second.rect))
        r->contains.push_back(second.name);
      if (second.rect.contains(first.rect))
        r->containedBy.push_back(first.name);
      if (first.rect.touches(second.rect))
        r->touches.push_back(second.name);
    }
  }

  if (outFilename.empty()) {
    std::cout << "Results:" << std::endl;
    printResults(std::cout, results);
  } else {
    std::cout << "Writing output to file: " << outFilename << std::endl;
    std::ofstream outFile(outFilename, std::ios::out);
    if (!outFile.is_open()) {
      std::cerr << "Could not open output file for writing: " << outFilename
          << std::endl;
      return 1;
    }
    printResults(outFile, results);
  }

  return 0;
}
