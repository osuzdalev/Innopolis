#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS  3
#define TFILE 10
#define FILE_LIMIT 12

//global variable that needs synchronization
int file = 0;
//Lock to be used while in critical region
pthread_mutex_t lock;
//condition to be met before accessing lock
pthread_cond_t condition;

void *writers(void *t){
	int i;
	long my_id = (long)t;

	for (i=0; i<TFILE; i++){
	  pthread_mutex_lock(&lock);
	  file++;

	  /* 
	  Check the value of file and signal waiting thread when condition is
	  reached. Note that this occurs while mutex is locked. 
	  */
	  if (file == FILE_LIMIT){
		 pthread_cond_signal(&condition);
		 printf("writers(): thread %ld, file = %d  Threshold reached.\n", 
				  my_id, file);
		 }
	  printf("writers(): thread %ld, file = %d, unlocking mutex\n", 
	    my_id, file);
	  pthread_mutex_unlock(&lock);

	  /* Do some "work" so threads can alternate on mutex lock */
	  sleep(1);
	}
	pthread_exit(NULL);
}

void *readers(void *t){
	long my_id = (long)t;

	printf("Starting readers(): thread %ld\n", my_id);
	/*
	Lock mutex and wait for signal. Note that the pthread_cond_wait 
	routine will automatically and atomically unlock mutex while it waits. 
	Also, note that if file_LIMIT is reached before this routine is run by
	the waiting thread, the loop will be skipped to prevent pthread_cond_wait
	from never returning. 
	*/
	pthread_mutex_lock(&lock);
	while (file<FILE_LIMIT){
	  pthread_cond_wait(&condition, &lock);
	  printf("readers(): thread %ld Condition signal received.\n", my_id);
	}
	file += 125;
	printf("readers(): thread %ld file now = %d.\n", my_id, file);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	int i;
	//visual thread ids
	long t1=1, t2=2, t3=3;
	pthread_t threads[NUM_THREADS];

	/* Initialize mutex and condition variable objects */
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init (&condition, NULL);

	pthread_create(&threads[0], NULL, readers, (void *)t1);
	pthread_create(&threads[1], NULL, writers, (void *)t2);
	pthread_create(&threads[2], NULL, writers, (void *)t3);

	/* Wait for all threads to complete */
	for(i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);

	/* Clean up and exit */
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&condition);
	pthread_exit(NULL);
} 
