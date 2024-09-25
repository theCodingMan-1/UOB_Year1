OPTIONS = -std=c11 -Wall -pedantic -g
ENDING = -fsanitize=undefined -fsanitize=address

.PHONY: square
square:
	clang $(OPTIONS) square.c -o square \
		$(ENDING)
	./square

.PHONY: interest
interest:
	clang $(OPTIONS) interest.c -o interest \
		$(ENDING)
	./interest

.PHONY: largestInt
largestInt:
	clang $(OPTIONS) largestInt.c -o largestInt \
		$(ENDING)
	./largestInt