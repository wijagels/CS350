CC=gcc
CFLAGS=-c -g -O3 -Wall -std=c11 -lrt
LDFLAGS=
SOURCES=Vector.c Main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vector
RUN=./$(EXECUTABLE)
RUNV=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(RUN)
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
