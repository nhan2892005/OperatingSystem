#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
   pthread_mutex_t lock;
   int pshared;
   int val=0;

   pthread_mutex_init(&lock, NULL);
   pthread_mutex_lock(&lock);
   val++;
   pthread_mutex_unlock(&lock);

   printf("val %5d\n", val);

   return 0;
}
