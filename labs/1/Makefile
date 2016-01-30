CC=gcc
CFLAGS=-c -Wall -g -std=c11
LDFLAGS=
SOURCES=Main.c Generate.c Normal.c mytimer.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab1

ccred:=$(shell echo "\033[0;31m")
ccgreen:=$(shell echo "\033[0;92m")
ccyellow:=$(echo -e "\033[0;33m")
ccend:=$(shell echo "\033[0m")


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o

test: all
	@echo "$(ccgreen)Running basic test$(ccend)"
	echo "130\n131\n119\n108" | ./lab1 -M 1000 -n 4
