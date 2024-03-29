/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
// pthread.h included in header.h

// implement shared queue, final histogram here..

// Add a node to the queue
void addNode(char* l, int i) {
  struct node* n = malloc(sizeof(struct node));
  char* ln = malloc(max_char);
  strcpy(ln,l);

  n->line = ln;
  n->lineNumber = i;
  n->next = NULL;
  // if queue is empty, set this as head and tail
  if (head==NULL) {
    head = n;
    tail = head;
  } else {
    tail->next = n;
    tail = n;
  }
}

// Get the head and removes it from queue
struct node* getHead() {
  if (head == NULL) {
    return NULL;
  }
  struct node* h = head;
  head = head->next;
  return h;
}

// Check if queue is empty
int isEmpty() {
// if head is null then queue is empty
  if(head == NULL) {
    return -1;
  } else {
    return 0;
  }
}

void createResult() {
  //format histogram from int array and write to file
	FILE *out;
	out = fopen("result.txt","w+");
	for(int i =0;i<26;i++){
		fprintf(out,"%c: %d\n",i+97,totals[i]);
	}
	fclose(out);
}

// Prints all nodes in queue
void printall() {
  struct node* n = head;
  if (head = tail) {
    head->next = NULL;
  }
  while(n != NULL) {
    printf("%s\n", n->line);
    n = n->next;
  }
}
