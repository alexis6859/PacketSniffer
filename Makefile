CXX = c++
Target = build/sniffer

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
SRCS = src/*.cpp

.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(Target)