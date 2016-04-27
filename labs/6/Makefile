CC=gcc
CFLAGS=-c -O3 -g -Wall -std=c11 -lpthread -D_XOPEN_SOURCE=700
LDFLAGS=-lpthread
SOURCES=Main.c Market.c Stock.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab6
RUN=./$(EXECUTABLE)
RUNV=valgrind --leak-check=full --track-origins=yes $(RUN)
RUNS=perf stat $(RUN)

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
	$(RUN) 55 10
