C=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c comandos.c parser.c histbuf.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=shiii

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

