/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header.h"

pthread_mutex_t totals_lock;
pthread_mutex_t llist_lock;
pthread_mutex_t cond_lock;
pthread_cond_t new_package;
pthread_cond_t package_consumed;

void *producer(void * args) {
    FILE *fptr = (FILE*) args;

    if(logFlag) {
      fprintf(logFile, "producer\n");
    }

    char c[max_char];
    int currentLine;

    // Read file line by line
    while(fgets(c, max_char, fptr) != NULL) {
       struct node* n1;
       pthread_mutex_lock(&llist_lock);
       addNode(c, currentLine);
       if(logFlag) {
         fprintf(logFile, "producer %d\n", currentLine);
       }
       currentLine++;
       packages++;
       printf("queue_size %d queue_size_set %d packages %d\n", queue_size, queue_size_set, packages);
       if(queue_size_set && packages >= queue_size){
         printf("waiting\n");
         pthread_cond_wait(&package_consumed,&llist_lock);
       }
       pthread_mutex_unlock(&llist_lock);
       pthread_cond_signal(&new_package);
    }
    // Set end of file flag
    eof = 1;
    if(logFlag) {
      fprintf(logFile, "producer %d\n", -1);
    }
    pthread_mutex_lock(&llist_lock);
    pthread_cond_broadcast(&new_package);
    pthread_mutex_unlock(&llist_lock);

}
