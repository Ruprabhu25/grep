all: example

example: example.c
	gcc -Wall -Wextra -Werror -o example example.c

clean:
	rm -f example
