#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
   pthread_rwlock_t lock;
   int pshared;
   int val=0;

   pthread_rwlock_init(&lock, NULL);

   pthread_rwlock_rdlock(&lock);
   printf("val %5d\n", val);
   pthread_rwlock_unlock(&lock);

   pthread_rwlock_wrlock(&lock);
   val++;
   pthread_rwlock_unlock(&lock);
   printf("val %5d\n", val);

   return 0;
}
