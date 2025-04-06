#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int main()
{
   sem_t sem;
   int pshared;
   int val=0;

   sem_init(&sem, 0, 5);
   sem_wait(&sem);
   val++;
   sem_post(&sem);

   printf("val %5d\n", val);

   return 0;
}
