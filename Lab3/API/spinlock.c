#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
   pthread_spinlock_t lock;
   int pshared;
   int val=0;

   pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED);
   pthread_spin_lock(&lock);
   val++;
   pthread_spin_unlock(&lock);

   printf("val %5d\n", val);

   return 0;
}
