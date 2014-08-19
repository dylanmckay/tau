# Makefile

CXX  := g++
LD   := g++
RM   := rm -f

BIN   := test

CXXFLAGS  := --std=c++11 -I../include -g -Wall -Werror
LDFLAGS   := 
LIBS      := ../modules/libtauopengl/libtauopengl.a \
             ../modules/libtaugraphics/libtaugraphics.a \
             ../modules/libtaumath/libtaumath.a \
             ../modules/libtaucore/libtaucore.a \
             $(shell pkg-config --libs icu-uc) \
             -lX11 -lGL -lGLU


CXX_SOURCE_FILES := $(shell find -name "*.cpp")
CXX_OBJECT_FILES := $(patsubst %.cpp,%.o,$(CXX_SOURCE_FILES))

DEPS := $(CXX_OBJECT_FILES:.o=.d)

.PHONY: $(BIN)

all: $(BIN)

clean:
	$(RM) $(CXX_OBJECT_FILES) $(DEPS) $(BIN)

rebuild: clean all

$(BIN): $(CXX_OBJECT_FILES)
	$(MAKE) -C ../modules/
	$(LD)  $(CXX_OBJECT_FILES) $(LDFLAGS) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) -c -MMD -MP $< -o $@ $(CXXFLAGS)

-include $(DEPS)

