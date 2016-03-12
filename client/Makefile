CC=g++
CFLAGS=-std=c++11

all: client state

state: gamestate.cpp gamestate.h
	$(CC) -c gamestate.cpp $(CFLAGS)

client: client.cpp client.h
	$(CC) -c client.cpp $(CFLAGS)

clean:
	rm -f *.o *~ client
