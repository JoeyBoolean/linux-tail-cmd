/*
Joey Bachand
EECS:jjbachan
StuID:z294u882
Program 2
10/30/2013
*/

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1028


struct node_s {
	char line[BUF_SIZE];
	struct node_s *next;
};

static void usage(void);

int main(int argc, char *argv[]) {

	struct node_s *head, *temp;
	char buffer[BUF_SIZE];
	char *ap;
	char *file;
	int fileFlag = 0;
	FILE* pFile;
	int i, n = 10;

	/* Parsing arguments */
	while(ap = *++argv) {
		if (ap[0] == '-') {
			if(ap[1] == '-')
				usage();
			else 
				n = atoi(ap)*(-1);
		}

		else{
			pFile = fopen(ap, "r");
			if(pFile == NULL)
				usage();
			fileFlag = 1;
		}
	}


	head = (struct node_s *) malloc( sizeof(struct node_s));
	temp = head;


	/*Create circular linked list with N nodes. N is 10 by default*/
	for(i=n; i>1; i--){
		temp->next = (struct node_s *) malloc( sizeof(struct node_s));
		strcpy(temp->line,"");
		temp = temp->next;
	}

	temp->next = head;
	temp = head;


	/*Read from file or STDIN into circular linked list*/
	if(fileFlag == 0){
		while(fgets (buffer, BUF_SIZE, stdin) != NULL){
			strcpy(temp->line, buffer);
			temp = temp->next;
		}
	}
	else{
		while(fgets (buffer, BUF_SIZE, pFile) != NULL){
			strcpy(temp->line, buffer);
			temp = temp->next;
		}
	}

	/*Print from linked list by starting at the last-in-node and
	moving to the next node then printing that nodes value. Traverse
	the list, printing each nodes value until you reach the node you 
	started at, then print that nodes value.*/

	head = temp;
	while(temp->next != head){
		printf("%s", (temp->line));
		temp = temp->next;
	}
	if(n != 0)
		printf("%s", temp->line);
	



	return 0;

}

/*Help/Error message*/
static void
usage(void)
{
	(void)fprintf(stderr,
	    "usage: tail [-n]"
	    " [file ...]\n");
	exit(1);
}