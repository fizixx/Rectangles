CXX = g++
CXXFLAGS = -std=c++11 -O0 -g -Wall -Wextra -pedantic

OBJS = main.o named_rect.o

all: rectangles tests

# ----- rectangles -----

rectangles: $(OBJS)
	$(CXX) -o rectangles $(OBJS)

main.o: main.cpp named_rect.h rect.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

named_rect.o: named_rect.cpp named_rect.h rect.h
	$(CXX) $(CXXFLAGS) -c named_rect.cpp -o named_rect.o

# ----- tests -----

tests: rect_test

rect_test: rect_test.cpp rect.h
	$(CXX) $(CXXFLAGS) rect_test.cpp -o rect_test

# ----- clean -----

clean:
	rm -rf rectangles rect_test
	rm -rf *.o
