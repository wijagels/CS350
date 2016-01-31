CC=gcc
CFLAGS=-c -g -O3 -Wall -std=c11
LDFLAGS=
SOURCES=Main.c Generate.c Normal.c mytimer.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab1
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
	@echo "$(ccgreen)Running basic test$(ccend)"
	echo "130\n131\n119\n108" | $(RUN) -n 4
	@echo "$(ccgreen)Running file test$(ccend)"
	-rm out.txt outcount.txt
	$(RUN) -i in.txt -M 1000 -o out.txt -c outcount.txt
	@echo "$(ccgreen)Displaying contents of out.txt$(ccend)"
	cat out.txt
	@echo "$(ccgreen)Displaying contents of outcount.txt$(ccend)"
	cat outcount.txt
	@echo "$(ccgreen)Generating 10 random numbers between 97 and 122 then running sort mode$(ccend)"
	$(RUN) -n 10 -m 97 -M 122 -g | $(RUN) -n 10 -m 97 -M 122
	@echo "$(ccgreen)Running output pipe test$(ccend)"
	$(RUN) -g | $(RUN)
	@echo "$(ccgreen)Running redirection test$(ccend)"
	$(RUN) -g > myfile.txt
	@echo "$(ccgreen)Running input pipe test$(ccend)"
	cat myfile.txt | $(RUN)
	@echo "$(ccgreen)Running performance test with 100,000 random numbers$(ccend)"
	$(RUN) -g -n 100000 -M 100000 | $(RUNS) -n 100000 -M 100000 -o /dev/null -c /dev/null
