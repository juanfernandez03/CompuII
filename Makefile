CFLAGS= -g -Wall
LDLIBS=-lrt -pthread
CC:=gcc
TARGETS= server 

all: clean $(TARGETS)
server: main.c http_worker.c command.c logWrite.c ipv4.c ipv6.c hilo.c login.c initRam.c initMemory.c ipvDefault.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: test
test:
	./server -d www/	

.PHONY: clean
clean:
	rm -f *.o *~ $(TARGETS)
