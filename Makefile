CXX = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb -fsanitize=address,undefined
STD = -std=c++17
SOURCES = $(wildcard src/*.cpp)
INCLUDE = $(shell find  include)
EXE = graph
ifdef SAN
	CFLAGS += -fsanitize=address,undefined
else
	CFLAGS += -O2
endif
.PHONY: all clean run $(EXE)

all: $(EXE)

$(EXE): $(SOURCES) $(INCLUDE)
	$(CXX) $(CFLAGS) $(SOURCES) -o $@

run:
	./$(EXE)

clean:
	$(RM) $(EXE)
