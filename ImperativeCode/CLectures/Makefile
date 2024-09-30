OPTIONS = -std=c11 -Wall -pedantic -g
ENDING = -fsanitize=undefined -fsanitize=address

.PHONY: test
test:
	clang $(OPTIONS) test.c -o test \
		$(ENDING)
	./test

.PHONY: LJ
LJ:
	clang $(OPTIONS) LoopsJumps.c -o LoopsJumps \
		$(ENDING)
	./LoopsJumps