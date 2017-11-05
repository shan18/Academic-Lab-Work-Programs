/*
 * Name: Shantanu Acharya
 * Date: 15th Oct, 2017
 * Language: C
 * Description: Solution for Producer-Consumer Problem using semaphores and mutex lock.
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>					// For using sleep();

#define BUFFER_SIZE 5				// max buffer size
#define NUM_PRO 3					// number of producers
#define NUM_CON 3					// number of consumers
#define NUM_ITERS 4					// number of items produced/consumed by each producer/consumer

typedef struct {
	int buffer[BUFFER_SIZE];		// shared variable
	int in;							// first empty slot
	int out;						// first full slot
	sem_t empty;					// number of empty slots
	sem_t full;						// number of full slots
	pthread_mutex_t mutex;			// mutual exclusion for the shared data
} t_sync;

t_sync shared;


void *Producer(void *arg) {

	int i, item, index;

	index = (intptr_t)arg;			// thread id

	for(i = 0; i < NUM_ITERS; i++) {
		item = i;					// produce an item

		/*
		 * If no empty slots available, then wait.
		 * A thread moves forward only if `&shared.empty` is non-zero.
		*/
		sem_wait(&shared.empty);

		// Check if some process is already using its critical section.
		pthread_mutex_lock(&shared.mutex);

		shared.buffer[shared.in] = item;
		shared.in = (shared.in + 1) % BUFFER_SIZE;
		printf("Producer %d is producing item %d..\n", index, item);
		fflush(stdout);

		pthread_mutex_unlock(&shared.mutex);	// Release the mutex lock
		sem_post(&shared.full);					// Increment the count of full slots by one

		if (i % 2 == 1) sleep(1);		// Interleave  producer and consumer execution
	}
}


void *Consumer(void *arg) {

	int i, item, index;

	index = (intptr_t)arg;		// thread id

	for(i = NUM_ITERS; i > 0; i--) {

		/*
		 * If no full slot available, then wait.
		 * A thread moves forward only if `&shared.full` is non-zero.
		*/
		sem_wait(&shared.full);

		// Check if some process is already using its critical section.
		pthread_mutex_lock(&shared.mutex);

		item = shared.buffer[shared.out];		// consume an item
		shared.out = (shared.out + 1) % BUFFER_SIZE;
		printf("Consumer %d is consuming item %d..\n", index, item);
		fflush(stdout);

		pthread_mutex_unlock(&shared.mutex);	// Release the mutex lock
		sem_post(&shared.empty);				// Increment the count of empty slots by one

		if (i % 2 == 1) sleep(1);		// Interleave  producer and consumer execution
	}
}


int main() {

	pthread_t producer_thread, consumer_thread;
	int index;

	/*
	 * Initialize the full and empty semaphores.
	 *
	 * 2nd parameter initialized to zero means that
	 * the semaphore can be shared by different threads of the same process.
	 *
	 * 3rd parameter gives the initial values of the semaphores.
	*/
	sem_init(&shared.full, 0, 0);
	sem_init(&shared.empty, 0, BUFFER_SIZE);

	pthread_mutex_init(&shared.mutex, NULL);	// Initialize the mutex

	// create producers
	for (index = 0; index < NUM_PRO; index++)
		pthread_create(&producer_thread, NULL, Producer, (void *)(intptr_t)index);	// use either long or intptr_t

	// create consumers
	for (index = 0; index < NUM_CON; index++)
		pthread_create(&consumer_thread, NULL, Consumer, (void *)(intptr_t)index);

	pthread_exit(NULL);
}
