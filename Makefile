RANGE_V3_ROOT ?= range-v3
INCLUDE_DIRS = -I$(RANGE_V3_ROOT)/include

CXX ?= g++-7
CXX_STD ?= -std=c++1z
CXXFLAGS = $(CXX_STD) -O3 -march=native $(INCLUDE_DIRS)

SRCFILES = $(wildcard src/*.cpp)
BINFILES = $(patsubst %.cpp, %, $(SRCFILES))


.PHONY: all clean

all: $(BINFILES)

clean:
	 rm -vf $(BINFILES)
