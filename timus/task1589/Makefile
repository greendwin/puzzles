EXECUTABLE=task1589.elf
SOURCES=main.cpp level.cpp
HEADERS=mask.h level.h

CFLAGS=-std=c++11 -Wall -Wextra -Wno-c++1z-extensions
LINKFLAGS=-lstdc++

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	clang $(LINKFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(HEADERS)
	clang $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
