CFLAGS= -g -Wall
LDLIBS=-lrt 
CC:=gcc
TARGETS= server 

all: clean $(TARGETS)
server: main.c http_worker.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: test
test:
	./server -d www/	

.PHONY: clean
clean:
	rm -f *.o *~ $(TARGETS)
