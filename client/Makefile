CC=g++

all: tools client session

state: gamestate.cpp gamestate.h
	$(CC) -std=c++11 -c gamestate.cpp 

session: commands.cpp session.cpp
	$(CC) -std=c++11 -c commands.cpp session.cpp

tools: tools.cpp tools.o
	$(CC) -std=c++11 -c tools.cpp 

client: client.cpp client.h
	$(CC) -std=c++11 -c client.cpp 

clean:
	rm -f *.o *~ client
