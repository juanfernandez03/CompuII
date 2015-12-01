CC = gcc 
CFLAGS= -g -Wall
TARGETS = server
all: $(TARGETS)

# objetivo: dependencias
#	reglas ( tab )

server: server.c
	$(CC) $(CFLAGS) -o $@ $^


test: tp3
#	ls *.txt | ./tp2
	#cat salida.txt

clean:
#	rm -fv $(TARGETS) *.o salida.txt 
