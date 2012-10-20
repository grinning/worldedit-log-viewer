CC=g++
SOURCES=src/main.cpp src/region.cpp src/timestamp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=welog

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)
.cpp.o:
	$(CC) -c $< -o $@ $(LIBS)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXECUTABLE)
emacs-clean:
	-rm -f src/*~
	-rm -f src/#*#
	-rm -f *~
	-rm -f #*#
