/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header.h"
// pthread.h included in header.h

void *producer(void * args) {
    FILE *fptr = (FILE*) args;

    char c[max_char];

    while(fgets(c, max_char, fptr) != NULL && num_items < queue_size) {
       struct node* n1;
       pthread_mutex_lock(&llist_lock);
       addNode(c);
       num_items++;
       printf("update num_items %d\n", num_items);
       pthread_cond_signal(&new_package);
       pthread_mutex_unlock(&llist_lock);
    }

    sleep(1);

    eof = 1;
    pthread_cond_signal(&new_package);
    pthread_cond_signal(&new_package);

    //pthread_cond_broadcast(&new_package);

}
