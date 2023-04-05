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

void parsefile(char filename[], int is_numbered, int is_colored) {
	FILE *fp;
	fp = fopen(filename, "r");
	char *line = NULL;
	size_t buffer_size = 1024;
	line = (char *)malloc(buffer_size * sizeof(char));
	struct node* head2 = NULL;
	int line_number = 1;
	while(!feof(fp)){
		getline(&line,&buffer_size,fp);
		//sscanf(line, filename, "%s");
		//printf("%s\n", line);
		head2 = head;
		while (head2 != NULL) {
			//printf("Pattern at %s", strstr(line, head2->val));
			if (strstr(line, head2->val) != NULL) { // if pattern is in string
				if (is_numbered == 1) {
					printf("%d: ", line_number);
				}
				if (is_colored == 1) {
					printf("%.*s", strlen(line) - strlen(strstr(line, head2->val)), line);
					printf(COLOR_CODE "%s" RESET_CODE, head2->val);
					printf("%s", strstr(line, head2->val) + strlen(head2->val));
				}
				else {
					printf("%s",line);
				}
			}
			head2 = head2->next;
			line_number++;
		}
	}
	return;
}

// determine which commands are being used
void iterate_commands(char *argv[], int argc) {
	int is_numbered = 0;
	int is_colored = 0;
	int help = 0;
	//printf("here\n");
	int len = argc;
	//printf("%d\n", len);
	int i = 1;
	while (i < len) {
		if (strcmp(argv[i],"-h") == 0) {
			printf("Usage: ./sgrep [-n] [-c] [-p PATTERN]... FILE...\n");
			return;
		}
		else if (strcmp(argv[i],"-n") == 0) {
			printf("numbered!\n");
			is_numbered = 1;
		}
		else if (strcmp(argv[i],"-c") == 0) {
			printf("colored\n");
			is_colored = 1;
		}
		else if (strcmp(argv[i],"-p") == 0) {
			printf("pattern\n");
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
	char str[] = "I love ECS150!";
	char *love = "love";

	//printf("%.*s", 2, str);
	//printf(COLOR_CODE "%s" RESET_CODE, love);
	//printf("%s\n", strstr(str, love) + strlen(love));
	iterate_commands(argv,argc);
	//make_linked_list(str);
	//printf("%s",strstr(str,love) + strlen(love));

	return 0;
}
