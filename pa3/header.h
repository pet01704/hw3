/*test machine: CSELAB_machine_name * date: 11/13/19
* name: Tseki Lhamo , Daniel Peterson
* x500: lhamo012 , pet01704 */

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
  int lineNumber;
  struct node* next;
};

int logFlag;
FILE* logFile;

void *producer(void * args);
void *consumer(void * args);

struct node* head;
struct node* tail;
void addNode(char* l, int i);
struct node* getHead();
int isEmpty();
void createResult();
void printall();

extern pthread_mutex_t totals_lock;
extern pthread_mutex_t llist_lock;
extern pthread_mutex_t cond_lock;
extern pthread_cond_t new_package;
extern pthread_cond_t package_consumed;

int packages;
int queue_size;
int queue_size_set;
int num_items;
int totals[26];
int eof;

#endif
