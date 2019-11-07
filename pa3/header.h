/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

/*
header.h, header for all source files
it will:
- structure definition
- global variable, lock declaration (extern)
- function declarations
*/
#include <pthread.h>

#ifndef _HEADER_H_
#define _HEADER_H_

struct node{
  char *line;
  struct node* next;
};

struct node* addNode(char* l);
struct node* getHead();
int isEmpty();
void printall();

struct node* head;
struct node* tail;
pthread_mutex_t m;
pthread_cond_t cond;

int eof;

#endif
