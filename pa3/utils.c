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
struct node* addNode(char* l) {
  struct node* n = malloc(sizeof(struct node));
  n->line = l;
  n->next = NULL;
  // if queue is empty, set this as head and tail
  if (head==NULL) {
    head = n;
    tail = n;
  }
  tail->next = n;
  tail = n;
  return n;
}

// Get the head and removes it from queue
struct node* getHead() {
  if (head == NULL) {
    return NULL;
  }
  struct node* h = head;
  head = head->next;
  // return the head
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

void printall() {
  struct node* n = head;
  while(n != NULL) {
    printf("%s", n->line);
    n = n->next;
  }
}
//
// int main()
// {
//   struct node* n1;
//   struct node* n2;
//   struct node* n3;
//   struct node* n4;
//
//
//   n1 = addNode("hello");
//   n2 = addNode("world");
//   n3 = addNode("this");
//   n4 = addNode("works");
//   printall();
//   printf("isEMpty: %d\n", isEmpty());
//   printf("Head is: %s\n", getHead()->line);
//   printf("Head is: %s\n", getHead()->line);
//   printf("Head is: %s\n", getHead()->line);
//   printf("Head is: %s\n", getHead()->line);
//   printf("Head is: %s\n", getHead()->line);
//
// }
