#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_CODE	"\e[0;31m" /* Red */
#define RESET_CODE	"\e[0;0m"

// node struct which holds pattern characters
struct node {
	char* val;
	struct node* next;
};

struct node *head = NULL;
struct node *current = NULL;
// add node to end of linked list
void add_node(char* pattern) {
	// create new node with value of pattern
	struct node *newNode = malloc(sizeof(struct node));
	newNode->val = pattern;
	newNode->next = NULL;

	//if head is NULL, the list is empty
	if(head == NULL) {
		head = newNode;
		current = head;
	}
	//else, find the last node and add newNode
	else
	{
		//add the newNode at the end of the linked list
		current->next = newNode;
		current = current->next;
	}
}
// parse file line by line and see if any patterns are in the line
void parsefile(char filename[], int is_numbered, int is_colored) {
	// open file
	FILE *fp;
	fp = fopen(filename, "r");
	// create line buffer to hold each line of the file
	char *line = NULL;
	size_t buffer_size = 1024;
	line = (char *)malloc(buffer_size * sizeof(char));

	struct node* head2 = NULL;
	int line_number = 1;
	// read file until end is reached
	while(!feof(fp)){
		// fill line buffer
		getline(&line,&buffer_size,fp);
		head2 = head;
		// for each line, go through pattern linked list
		while (head2 != NULL) {
			// check if pattern is found in the line
			if (strstr(line, head2->val) != NULL) { // if pattern is in string
				// print line number if -n was a command line argument
				if (is_numbered == 1) {
					printf("%d: ", line_number);
				}
				// print colored patter if -c was a command line argument
				if (is_colored == 1) {
					// split line into substrings before, at, and after pattern occurrence
					printf("%.*s", (int)(strlen(line) - strlen(strstr(line, head2->val))), line);
					printf(COLOR_CODE "%s" RESET_CODE, head2->val);
					printf("%s", strstr(line, head2->val) + strlen(head2->val));
				}
				// if -c is not a command line argument, then just print the whole line
				else {
					printf("%s",line);
				}
			}
			// go to next node in linked list
			head2 = head2->next;
		}
		// increase line number
		line_number++;
	}
	return;
}

// determine which commands are being used
void iterate_commands(char *argv[], int argc) {
	int is_numbered = 0;
	int is_colored = 0;
	int len = argc;
	int i = 1;
	while (i < len) {
		if (strcmp(argv[i],"-h") == 0) {
			printf("Usage: ./sgrep [-n] [-c] [-p PATTERN]... FILE...\n");
			return;
		}
		else if (strcmp(argv[i],"-n") == 0) {
			is_numbered = 1;
		}
		else if (strcmp(argv[i],"-c") == 0) {
			is_colored = 1;
		}
		else if (strcmp(argv[i],"-p") == 0) {
			i = i + 1;
			printf("%s\n", argv[i]);
			add_node(argv[i]);
		}
		i = i + 1;
	}
	char* filename = argv[len-1];
	parsefile(filename, is_numbered, is_colored);
	return;
}

int main(int argc, char *argv[])
{
	iterate_commands(argv,argc);
	return 0;
}
