all : program

program: second.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 second.c -o second -lm

clean:
	rm -f second
