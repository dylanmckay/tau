# Makefile

CXX  := g++
AR   := ar
RM   := rm -f

BIN   := libtaucore.a

CXXFLAGS  := --std=c++11 -Wall -Werror -g -I../../include

CXX_SOURCE_FILES := $(shell find src/ -name "*.cpp")
CXX_OBJECT_FILES := $(patsubst %.cpp,%.o,$(CXX_SOURCE_FILES))

DEPS := $(CXX_OBJECT_FILES:.o=.d)

all: $(BIN)

clean:
	$(RM) $(CXX_OBJECT_FILES) $(DEPS) $(BIN)

rebuild: clean all

$(BIN): $(CXX_OBJECT_FILES)
	$(AR) rcu $@ $(CXX_OBJECT_FILES)

%.o: %.cpp
	$(CXX) -c -MMD -MP $< -o $@ $(CXXFLAGS)

-include $(DEPS)

