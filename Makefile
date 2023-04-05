all: sgrep

sgrep: sgrep.c
	gcc -Wall -Wextra -Werror -o sgrep sgrep.c

clean:
	rm -f sgrep
