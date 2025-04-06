#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define BUF_SIZE 2
#define THREADS 1 // 1 producer and 1 consumer
#define LOOPS 3 * BUF_SIZE // variable

// Initiate shared buffer
int buffer[BUF_SIZE];
int fill = 0;
int use = 0;

/*TODO: Fill in the synchronization stuff */

void put(int value); // put data into buffer
int get();           // get data from buffer

void * producer(void * arg) {
  int i;
  int tid = *((int*) arg);
  for (i = 0; i < LOOPS; i++) {
    /*TODO: Fill in the synchronization stuff */
    put(i); // line P2
    printf("Producer %d put data %d\n", tid, i);
    sleep(1);
    /*TODO: Fill in the synchronization stuff */
  }
  pthread_exit(NULL);
}

void * consumer(void * arg) {
  int i, tmp = 0;
  int tid = *((int*) arg);
  while (tmp != -1) {
    /*TODO: Fill in the synchronization stuff */
    tmp = get(); // line C2
    printf("Consumer %d get data %d\n", tid, tmp);
    sleep(1);
    /*TODO: Fill in the synchronization stuff */
  }
  pthread_exit(NULL);
}

int main(int argc, char ** argv) {
  int i, j;
  int tid[THREADS];
  pthread_t producers[THREADS];
  pthread_t consumers[THREADS];

  /*TODO: Fill in the synchronization stuff */

  for (i = 0; i < THREADS; i++) {
    tid[i] = i;
    // Create producer thread
    pthread_create( & producers[i], NULL, producer, (void * ) &tid[i]);

    // Create consumer thread
    pthread_create( & consumers[i], NULL, consumer, (void * ) &tid[i]);
  }

  for (i = 0; i < THREADS; i++) {
    pthread_join(producers[i], NULL);
    pthread_join(consumers[i], NULL);
  }

  /*TODO: Fill in the synchronization stuff destroy (if needed) */

  return 0;
}

void put(int value) {
  buffer[fill] = value;          // line f1
  fill = (fill + 1) % BUF_SIZE; // line f2
}

int get() {
  int tmp = buffer[use];         // line g1
  buffer[use] = -1;              //clean the item
  use = (use + 1) % BUF_SIZE;   // line g2
  return tmp;
}