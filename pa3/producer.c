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
  //  FILE * fptr;
    int r;
    int linesCount;
    int ch = 0;

    // if((fptr = fopen("test2.txt", "r+")) == NULL) {
    //     printf("No such file\n");
    //     exit(1);
    // }

    // Calulate the number of lines in file
    while((ch=fgetc(fptr))!=EOF) {
      if(ch=='\n') {
        linesCount++;
      }
    }

    rewind(fptr);
    //char c[max_char*linesCount];
    char c[max_char];

    int i = 0;

    //while(fgets(c+(i*max_char), max_char*linesCount, fptr) != NULL) {
    while(fgets(c, max_char, fptr) != NULL) {
       struct node* n1;
       printf("before lock");
       pthread_mutex_lock(&llist_lock);
       //n1 = addNode(c + (i * max_char));
       n1 = addNode(c);
    //   printf("head: %s\n", getHead()->line);
    //   printf("is empty: %d\n", isEmpty());
       pthread_mutex_unlock(&llist_lock);
       pthread_cond_signal(&new_package);
       i++;
    }
    sleep(1);
    eof = 1;

    pthread_cond_broadcast(&new_package);
    printall();
}
