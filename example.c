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

void create_list(char* input_string) {
	//printf("Here\n");
    char *token;
    //printf("Here\n");
    /*get the first token */
    token = strtok(input_string, " ");
	//printf("Here\n");
    /* walk through other tokens */
	while( token != NULL ) {
    	//printf( " %s\n", token );
		struct node *newNode = malloc(sizeof(struct node));
		newNode->val = token;
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
		token = strtok(NULL, " ");
	}
	
}

int main(void)
{
	char str[] = "I love ECS150!";
	char *love = "love";

	printf("%.*s", 2, str);
	printf(COLOR_CODE "%s" RESET_CODE, love);
	printf("%s\n", strstr(str, love) + strlen(love));
	make_linked_list(str);

	return 0;
}
