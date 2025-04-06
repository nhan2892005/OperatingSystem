#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int MAX_COUNT = 1e9;
static int count = 0;

void *f_count(void *sid) {
  int i;
  for (i = 0; i < MAX_COUNT; i++) {
    count = count + 1;
  }

  printf("Thread %s: holding %d \n", (char *) sid, count);
}

int main() {
  pthread_t thread1, thread2;

  /* Create independent threads each of which will execute function */
  pthread_create( &thread1, NULL, &f_count, "1");
  pthread_create( &thread2, NULL, &f_count, "2");


  // Wait for thread th1 finish
  pthread_join( thread1, NULL);

  // Wait for thread th1 finish
  pthread_join( thread2, NULL);

  return 0;
}