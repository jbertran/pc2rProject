CC=ocamlc
LD=str.cma

all: link

link: interfaces gameState tools
	$(CC) -o gameState $(LD) gameState.cmo 

interfaces: *.mli
	$(CC) -c $^

gameState: interfaces gameState.ml
	$(CC) -c gameState.ml

clean: 
	rm -f *.cmi *.cmo *~
