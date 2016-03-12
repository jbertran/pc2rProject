CC=ocamlc
LD=str.cma

all: link

link: interfaces gameState
	$(CC) -o gameState $(LD) gameState.cmo

test: interfaces gameState test.cmo
	$(CC) -o test $(LD) gameState.cmo test.cmo

interfaces: *.mli
	$(CC) -c $^

%.cmo: %.ml
	$(CC) -c $<

gameState: interfaces gameState.ml
	$(CC) -c gameState.ml

clean: 
	rm -f *.cmi *.cmo *~
