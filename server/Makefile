CC=ocamlc
LD=-thread str.cma unix.cma threads.cma

all: link

link: interfaces gameState server
	$(CC) -o server $(LD) gameState.cmo server.cmo

server: server.ml gameState
	$(CC) -c -thread threads.cma unix.cma list.cma sys.cma server.ml

test: interfaces gameState.cmo server.cm test.cmo
	$(CC) -o test $(LD) gameState.cmo test.cmo

interfaces: *.mli
	$(CC) -c $^

%.cmo: %.ml
	$(CC) -c $< $(LDFLAGS)

gameState: interfaces gameState.ml
	$(CC) -c gameState.ml

clean: 
	rm -f *.cmi *.cmo *~
