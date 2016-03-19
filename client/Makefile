CC=g++
CFLAGS=-std=c++11 -Wall

all: tools client session repr

session: commands.cpp session.cpp
	$(CC) $(CFLAGS) -c commands.cpp session.cpp

repr: repr.cpp repr.h
	$(CC) $(CFLAGS) -c repr.cpp 

client: client.cpp client.h
	$(CC) $(CFLAGS) -c client.cpp 

tools: tools.cpp
	$(CC) $(CFLAGS) -c tools.cpp 

clean:
	rm -f *.o *~ client
