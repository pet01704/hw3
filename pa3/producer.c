/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
// pthread.h included in header.h

void producer(void * args) {
    FILE *fptr = (FILE*) args;
  //  FILE * fptr;
    int r;
    int linesCount;
    int ch = 0;

    // if((fptr = fopen("test2.txt", "r+")) == NULL) {
    //     printf("No such file\n");
    //     exit(1);
    // }

    while((ch=fgetc(fptr))!=EOF) {
      if(ch=='\n') {
        linesCount++;
      }
    }

    rewind(fptr);
    char c[1024*linesCount];
    int i = 0;

    pthread_mutex_init(&m, NULL);
    pthread_mutex_lock(&m);

    while(fgets(c+(i*1024), 1024*linesCount, fptr) != NULL) {
       struct node* n1;
       n1 = addNode(c + (i * 1024));
       i++;
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&m);
}


int main()
{
  producer();

  printall();
}
