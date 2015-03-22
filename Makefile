CXX = g++

# Full optimize with all warnings.
CXXFLAGS = -std=c++11 -O2 -g -Wall -Wextra -pedantic

all: rectangles tests

# ----- rectangles -----

OBJS = main.o named_rect.o

rectangles: $(OBJS)
	$(CXX) -o rectangles $(OBJS)

main.o: main.cpp named_rect.h rect.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

named_rect.o: named_rect.cpp named_rect.h rect.h
	$(CXX) $(CXXFLAGS) -c named_rect.cpp -o named_rect.o

# ----- tests -----

TESTS = rect_test

tests: $(TESTS)

rect_test: rect_test.cpp rect.h rectangles
	$(CXX) $(CXXFLAGS) rect_test.cpp -o rect_test

# ----- clean -----

clean:
	rm -rf rectangles $(TESTS)
	rm -rf *.o
