all: bitset.c bitset.h bloom.c bloom.h main.c
	gcc -Wall -O0 -g -o filter main.c bitset.c bloom.c -I. -lm

sanitize: bitset.c bitset.h bloom.c bloom.h main.c
	gcc -Wall -O0 -g -fsanitize=address -o filter main.c bitset.c bloom.c -I. -lm
