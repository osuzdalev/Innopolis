#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS  1000
//globally shared file
int main_file = 0;
//globally shared helping variable
int resource_counter = 0;
//lock to be used while performing action on file
pthread_mutex_t lock;
//conditions to be met before a thread can access lock
pthread_cond_t read_phase, write_phase;

void* readers(void* data){
	printf("Reader\n");
	//locking mutex
	pthread_mutex_lock(&lock);
	//checking for conditions
	while(resource_counter == -1){
		printf("Waiting for reader signal\n");
		pthread_cond_wait(&read_phase, &lock);
	}
	//incrementing global variable
	resource_counter++;
	//releasing lock for other threads to start work
	pthread_mutex_unlock(&lock);
	
	// !!! critical region !!!
	printf("Reader Critical Region\n");
	printf("File = %i \n", main_file);
	
	pthread_mutex_lock(&lock);
	printf("Reader leaving\n");
	resource_counter--;
	//if last reader, let writers know
	if(resource_counter == 0){
		printf("Sending Writer Signal\n");
		pthread_cond_signal(&write_phase);
	}
	pthread_mutex_unlock(&lock);
	return (void*)NULL;
}

void* writers(){
	printf("Writer \n");
	
	pthread_mutex_lock(&lock);
	while(resource_counter !=0){
		printf("Waiting for writer Signal \n");
		pthread_cond_wait(&write_phase, &lock);
	}
	resource_counter = -1;
	
	pthread_mutex_unlock(&lock);
	
	// !!! critical region !!!
	printf("Writer critical region\n");
	main_file++;
	
	pthread_mutex_lock(&lock);
	printf("Writer leaving\n");
	resource_counter = 0;
	printf("Sending Signals\n");
	pthread_cond_broadcast(&read_phase);
	pthread_cond_signal(&write_phase);
	
	pthread_mutex_unlock(&lock);
}

int main(){
	//declaring variable 'tid' of type thread
	pthread_t threads[NUM_THREADS];
	
	//Initialize mutex and condition variables
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&write_phase, NULL);
	pthread_cond_init(&read_phase, NULL);
	for(int i = 0; i<NUM_THREADS; i++){
		if(i%2 == 0){
			pthread_create(&threads[i], NULL, writers, (void *)main_file);
		}
		else {
			pthread_create(&threads[i], NULL, readers, (void *)main_file);
		}
	}
	
	for(int i = 0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	
	printf("DONE");
	
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&read_phase);
	pthread_cond_destroy(&write_phase);
	pthread_exit(NULL);
	
	return 0;
	
}