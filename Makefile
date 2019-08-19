
CXXFLAGS := -Wall -Wextra -O2 -g -std=c++11

LDFLAGS := -ledit

all: cribdrag

cribdrag: cribdrag.cpp file.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ cribdrag.cpp file.cpp

CLEAN := cribdrag
clean:
	rm -f $(CLEAN)

