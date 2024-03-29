CC=g++
CFLAGS=-c -g -std=c++11 
SOURCES=main.cpp Hashmap.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBS=
LDFLAGS=
PROGRAM=main

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDFLAGS) $(LIBS) 

.cpp.o: 
	$(CC) $(CFLAGS) $<

depend: .depend

.depend: $(SOURCES)
	rm -f .depend
	$(CC) $(CFLAGS) -MM $^ >> .depend;

include .depend

clean:
	rm -f .depend $(PROGRAM) $(OBJECTS)
	
run: all
	./$(PROGRAM)
