OPTIONS = -std=c11 -Wall -pedantic -g
ENDING = -fsanitize=undefined -fsanitize=address

.PHONY: test
test:
	clang $(OPTIONS) test.c -o test \
		$(ENDING)
	./test