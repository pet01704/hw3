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
#define max_char 1024

struct node{
  char *line;
  struct node* next;
};

void *producer(void * args);
void *consumer(void * args);

void addNode(char* l);
struct node* getHead();

int isEmpty();
void printall();

struct node* head;
struct node* tail;

pthread_mutex_t totals_lock;
pthread_mutex_t llist_lock;
pthread_mutex_t cond_lock;
pthread_cond_t new_package;

int linesCount;
int linesCompleted;
int queue_size;
int queue_size_set;
int num_items;
int totals[26];
int eof;

#endif
