OPTIONS = -std=c11 -Wall -pedantic -g
ENDING = -fsanitize=undefined -fsanitize=address

.PHONY: backwards
backwards:
	clang $(OPTIONS) backwards.c -o backwards \
		$(ENDING)
	./backwards