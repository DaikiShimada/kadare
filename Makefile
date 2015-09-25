CXX = g++
CXXFLAGS = -O3 -std=c++11
INCLUDE = -Iinclude
EXAMPLE_DIR := example
EXAMPLE_SRC := $(wildcard $(EXAMPLE_DIR)/*.cpp)
EXAMPLE_BIN := $(addprefix ./, $(EXAMPLE_SRC:.cpp=.bin))

.PHONY: all 

all : $(EXAMPLE_BIN)

# make example
%.bin : $(EXAMPLE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $<
