/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include "header.h"
// pthread.h included in header.h

int main(int argc, char *argv[]){

	//expects between 3 and 5 arguments
	if (argc < 3 || argc > 5) {
		printf("Wrong number of arguments.\n");
		printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
		exit(1);
	}

	//argv[1] is the number of consumers
	int n_consumers = 0;
	if ((n_consumers = atoi(argv[1])) <= 0){
		printf("Invalid #consumer. Given '%s', expected a positive integer.\n",argv[1]);
		printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
		exit(1);
	}

	//argv[2] is the filename
	FILE *fptr;
	if ((fptr = fopen(argv[2], "r")) == NULL){
		printf("Unable to open the file '%s'.\n",argv[2]);
		printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
		exit(1);
	}

	//argv[3] is the option
	if (argc > 3){
		if (!strcmp(argv[3],"-p")){
			logFlag = 1;
		}else if (!strcmp(argv[3],"-b")){
			queue_size_set = 1;
		}else if (!strcmp(argv[3],"-bp")){
			queue_size_set = 1;
			logFlag = 1;
		}else{
			printf("Invalid argument '%s'.\n",argv[3]);
			printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
			exit(1);
		}
	}

	//argv[4] is the queue size
	if (argc > 4){
		if(queue_size_set){
			sscanf(argv[4], "%d", &queue_size);
		}else{
			printf("Invalid argument '%s'.\n",argv[4]);
			printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
			exit(1);
		}
	}


	if (logFlag){
		if ((logFile = fopen("log.txt", "w+")) == NULL){
			printf("Unable to open log.txt.\n");
			exit(0);
		}
	}

	pthread_t producer_t;
	pthread_t consumer_t[n_consumers];


	//initialize histogram
	for(int i =0;i<26;i++){
		totals[i] = 0;
	}
	//initialize mutex lock for totals
	pthread_mutex_init(&totals_lock, NULL);
	pthread_mutex_init(&llist_lock, NULL);
	//pthread_mutex_init(&cond_lock, NULL);
	pthread_cond_init(&new_package, NULL);

	//create producer thread
	pthread_create(&producer_t, NULL, producer, fptr);


	//create n_consumer consumer threads
	for (int i = 0; i < n_consumers; i++){
		int id = i;
		pthread_create(&consumer_t[i], NULL, consumer, &id);
	}

	//wait for all threads to join back
	pthread_join(producer_t, NULL);
	for (int i = 0; i < n_consumers; i++){
		pthread_join(consumer_t[i], NULL);
	}

	//close fptr
	fclose(fptr);
	if (logFlag){
		fclose(logFile);
	}

	createResult();

	return 0;
}
