CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SERVER_DIR=./server/
SOURCES=main.c \
	$(SERVER_DIR)module.c \
	$(SERVER_DIR)core.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mediad

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o \
	$(SERVER_DIR)*o \
	mediad
