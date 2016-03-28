CC=ocamlc
LD=str.cma unix.cma threads.cma

all: link

link: interfaces gameState
	$(CC) -o gameState $(LD) gameState.cmo

interfaces: *.mli
	$(CC) -c $^

server: server.ml
	$(CC) -c -thread unix.cma threads.cma server.ml

test: interfaces gameState.cmo server.cm test.cmo
	$(CC) -o test $(LD) gameState.cmo test.cmo

gameState: interfaces gameState.ml
	$(CC) -c gameState.ml

clean: 
	rm -f *.cmi *.cmo *~ gameState server test
