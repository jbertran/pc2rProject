CC=g++
CFLAGS=-std=c++11

all: tools client

state: gamestate.cpp gamestate.h
	$(CC) -c gamestate.cpp $(CFLAGS)

tools: tools.cpp tools.o
	$(CC) -c tools.cpp $(CFLAGS)

client: client.cpp client.h
	$(CC) -c client.cpp $(CFLAGS)

clean:
	rm -f *.o *~ client
