n ?= 100000
path ?= sort/sort_numbers
# usage: make n=[whatever] path=[path to ur sorting executable]
serial: sort/sort_numbers
	python3 check.py $(n) $(path)

sort/sort_numbers: sort/sort_numbers.ml
	ocamlc -o sort/sort_numbers sort/sort_numbers.ml

.PHONY: clean

clean:
	rm check/check_numbers **/*.class sort/sort_numbers **/*.cmo **/*.cmi generate/NumberGenerator.class