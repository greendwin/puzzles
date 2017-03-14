EXECUTABLE=task1589.elf
SOURCES=task1589.cpp

CFLAGS=-Wall
LINKFLAGS=-lstdc++

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	clang $(LINKFLAGS) $(OBJECTS) -o $@

.cpp.o:
	clang $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
