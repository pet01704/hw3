/*test machine: CSELAB_machine_name * date: mm/dd/yy
* name: full_name1 , [full_name2]
* x500: id_for_first_name , [id_for_second_name] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
// pthread.h included in header.h

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

	if (logFlag){
		fprintf(logFile,"consumer %d\n",id);
	}

	while (! (eof && isEmpty())){
		pthread_mutex_lock(&llist_lock);
		while (isEmpty() && !eof){
			pthread_cond_wait(&new_package,&llist_lock);
			if (eof) {
				pthread_mutex_unlock(&llist_lock);
				return NULL;
			}
		}
		char* package ="";
		if (!isEmpty()){
			struct node* new_node = getHead();
			packages--;
			pthread_cond_signal(&package_consumed);			
			if (new_node != NULL){
				package = new_node->line;
				if (logFlag){
					fprintf(logFile,"consumer %d: %d\n",id,new_node->lineNumber);
				}
			}

		}
		pthread_mutex_unlock(&llist_lock);

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
