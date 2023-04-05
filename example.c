#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_CODE	"\e[0;31m" /* Red */
#define RESET_CODE	"\e[0;0m"

// check through command line first, create linked list of all commands, 


struct node {
	char* val;
	struct node* next;
};

struct node *head = NULL;
struct node *current = NULL;

void add_node(char* pattern) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->val = pattern;
	newNode->next = NULL;

	//if head is NULL, it is an empty list
	if(head == NULL) {
		head = newNode;
		current = head;
	}
	//Otherwise, find the last node and add the newNode
	else
	{
		//add the newNode at the end of the linked list
		current->next = newNode;
		current = current->next;
	}
}

// determine which commands are being used
void iterate_commands(char *argv[]) {
	int is_numbered = 0;
	int is_colored = 0;
	int help = 0;
	int len = sizeof(argv) / sizeof(char*);
	int i = 1;
	while (i < len) {
		if (strcomp(argv[i]) == "-h") {
			printf("Usage: ./sgrep [-n] [-c] [-p PATTERN]... FILE...\n");
			return;
		}
		else if (strcomp(argv[i]) == "-n") {
			is_numbered = 1;
		}
		else if (strcomp(argv[i]) == "-c") {
			is_colored = 1;
		}
		else if (strcomp(argv[i]) == "-p") {
			i = i + 1;
			add_node(argv[i]);
		}
		i = i + 1;
	}
	char filename[] = argv[len-1];
	parse_file(filename, is_numbered, is_colored);
	return;
}

void parse_file() {
	return;
}

int main(int argc, char *argv[])
{
	char str[] = "I love ECS150!";
	char *love = "love";

	printf("%.*s", 2, str);
	printf(COLOR_CODE "%s" RESET_CODE, love);
	printf("%s\n", strstr(str, love) + strlen(love));
	make_linked_list(str);

	return 0;
}
