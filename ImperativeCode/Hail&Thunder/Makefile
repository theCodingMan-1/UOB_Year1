OPTIONS = -std=c11 -Wall -pedantic -g
ENDING = -fsanitize=undefined -fsanitize=address

.PHONY: cube
cube:
	clang $(OPTIONS) cube.c -o cube \
		$(ENDING)
	./cube
	
.PHONY: sphere
sphere:
	clang $(OPTIONS) sphere.c -o sphere \
		$(ENDING)
	./sphere

.PHONY: factorial
factorial:
	clang $(OPTIONS) factorial.c -o factorial \
		$(ENDING)
	./factorial

.PHONY: collatz
collatz:
	clang $(OPTIONS) collatz.c -o collatz \
		$(ENDING)
	./collatz