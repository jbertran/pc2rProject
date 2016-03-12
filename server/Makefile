all: gameState tools

gameState: gameState.ml gameState.mli
	ocamlc -c gameState.mli
	ocamlc -c gameState.ml

tools: tools.ml tools.mli
	ocamlc -c tools.mli
	ocamlc -c tools.ml

clean: 
	rm -f *.cmi *.cmo *~
