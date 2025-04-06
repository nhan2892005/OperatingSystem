#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
   pthread_cond_t lock;
   pthread_mutex_t mtx;
   int pshared;
   int val=0;

   pthread_cond_init(&lock, NULL);
   pthread_mutex_init(&mtx, NULL);

   pthread_cond_wait(&lock,&mtx);
   val++;
   pthread_cond_signal(&lock);

   printf("val %5d\n", val);

   return 0;
}
