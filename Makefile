n ?= 1000000;
path ?= sort/sort_numbers
# usage: make n=[whatever] path=[path to ur sorting executable]
serial: sort/sort_numbers
	python3 check.py $(n) $(path)



sort/sort_numbers: sort/sort_numbers.cpp sort/merge_asm.s
	clang++ -std=c++11 -c sort/sort_numbers.cpp -o sort/sort_numbers.o
	as -o sort/merge_asm.o sort/merge_asm.s
	clang++ sort/sort_numbers.o sort/merge_asm.o -o sort/sort_numbers -pthread


.PHONY: clean

clean:
	rm check/check_numbers **/*.class sort/sort_numbers **/*.cmo **/*.cmi generate/NumberGenerator.class