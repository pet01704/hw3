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
struct timeval tv;
struct timespec ts;
 int rt;

    

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

	//argv[3] and argv[4] can be option or queue size for ec
	int option_set = 0;
	int queue_size_set = 0;
	for (int i = 3; i < argc; i ++){
		if (!strcmp(argv[i],"-p") && !option_set){
			option_set = 1;
		}else if (!strcmp(argv[i],"-b") && !option_set){
			option_set = 1;
		}else if (!strcmp(argv[i],"-bp") && !option_set){
			option_set = 1;
		}else if(!queue_size_set && (queue_size = atoi(argv[i]) > 0)){
			queue_size_set = 1;
		}else{
			printf("Invalid argument '%s'.\n",argv[i]);
			printf("Usage: $ %s #consumer filename [option] [#queue_size]\n",argv[0]);
			exit(1);   
		}
	}
	
	
	pthread_t producer_t;
	pthread_t consumer_t[n_consumers];

	
	//initialize counter
	linesCompleted = 0;
	

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
		pthread_create(&consumer_t[i], NULL, consumer, i); 
	}
	
	//wait for all threads to join back
	pthread_join(producer_t, NULL); 
	for (int i = 0; i < n_consumers; i++){
		pthread_join(consumer_t[i], NULL); 
	}

	//close fptr
	fclose(fptr);
	
	//format histogram from int array and write to file
	FILE *out;
	out = fopen("result.txt","w+");
	for(int i =0;i<26;i++){
		fprintf(out,"%c: %d\n",i+97,totals[i]);
	}
	fclose(out);



	return 0;
}

void count_words( char *str, int *totals){
	int reset = 1;
	int i = 0;
	while (str[i] != '\0') {
		char cur = tolower(str[i]);
   		if (cur >= 'a' && cur <= 'z') {
			if (reset){
				totals[cur - 'a']++;
				reset = 0;
			}
		}else{
			reset = 1;
		}
    		i++;
	}
}

void *consumer(void *args){
	
	//args is an int pointer
	int id = (int) args;
	printf("id: %d\n",id);
	while (! (eof && isEmpty())){
		pthread_mutex_lock(&llist_lock);
		
		while (isEmpty() && !eof){
			printf("cond %d\n",id);
			
			gettimeofday(&tv, NULL);
		    	ts.tv_sec = time(NULL) + (1000) / 1000;
		    	ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * ((1000) % 1000);
		    	ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
		    	ts.tv_nsec %= (1000 * 1000 * 1000);
			rt = pthread_cond_timedwait(&new_package,&llist_lock,&ts);//
			//sleep(1);
			printf("met %d\n",id);
			if (eof || rt){
				//pthread_cond_signal(&new_package);
				printf("%d\n",isEmpty());			
				return NULL;
			}
		}
		

		printf("waiting %d\n",id);
		//pthread_mutex_lock(&llist_lock);
		printf("locked %d\n",id);
		char* package;
		if (!isEmpty()){
			//pull package from llist
			struct node* new_node = getHead();
			package = new_node->line;
			printf("Producer recieved package %s",package);
			
		}
		printf("unlocking %d\n",id);

		pthread_mutex_unlock(&llist_lock);
		

		printf("unlocked %d\n",id);
		
		//do word count on the package
		int temp[26];
		for (int i =0; i < 26; i++){
			temp[i] = 0;
		}
		count_words(package, temp);

		//add results to histogram
		pthread_mutex_lock(&totals_lock);
		for (int i =0; i < 26; i++){
			totals[i] += temp[i];
		}
		pthread_mutex_unlock(&totals_lock);

		
		
	}
	

}
































