#valgrind --leak-check=full ./media-server
CC=cc
CFLAGS=-c -Wall
LDFLAGS=-ldl
SERVER_DIR=./server/
MODULES_DIR=./modules/

SOURCES=main.c \
	$(SERVER_DIR)module.c \
	$(SERVER_DIR)core.c \
	$(SERVER_DIR)connection.c \
	$(SERVER_DIR)config.c \
	$(SERVER_DIR)util.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=media-server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o \
	$(SERVER_DIR)*o \
	media-server
