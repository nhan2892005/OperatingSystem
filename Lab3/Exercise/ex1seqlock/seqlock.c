#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "seqlock.h"  /* TODO implement this header file */

pthread_seqlock_t lock;

int main()
{
   int val = 0;

   pthread_seqlock_init(&lock);

   pthread_seqlock_wrlock(&lock);
   val++;
   pthread_seqlock_wrunlock(&lock);


   if(pthread_seqlock_rdlock(&lock) == 1){
      printf("val = %d\n", val); 
      pthread_seqlock_rdunlock(&lock);
   }
}
