#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Define global data where everyone can see them */
#define NUMTHRDS 8
#define VECLEN 100000
int *a, *b; 
long sum=0;

// Add a mutex to protect the sum variable
pthread_mutex_t sum_mutex;

void *dotprod(void *arg)
{
  /* Each thread works on a different set of data.
   * The offset is specified by the arg parameter. The size of
   * the data for each thread is indicated by VECLEN.
   */
   int i, start, end, offset, len;

   long tid = *(long *)arg;     // Get the thread ID
   free(arg);                   // Free the allocated memory for arg

   offset = tid;
   len = VECLEN;
   start = offset*len;
   end   = start + len;

   // Calculate local sum for this thread to decrease mutex lock time
   long local_sum = 0;
   for (i = start; i < end; i++)
        local_sum += (a[i] * b[i]);

/* Perform my section of the dot product */
   // Update the global sum by using a mutex lock
   pthread_mutex_lock(&sum_mutex);
   printf("thread: %ld starting. start=%d end=%d\n",tid,start,end-1);
   sum += local_sum;
   printf("thread: %ld done. Global sum now is=%li\n",tid,sum);
   pthread_mutex_unlock(&sum_mutex);

   pthread_exit((void*) 0);
}



int main (int argc, char *argv[])
{
    long i;
    void *status;
    pthread_t threads[NUMTHRDS];
    pthread_attr_t attr;

    /* Assign storage and initialize values */
    a = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
    b = (int*) malloc (NUMTHRDS*VECLEN*sizeof(int));
    
    for (i=0; i<VECLEN*NUMTHRDS; i++)
        a[i]= b[i]=1;

    /* Create threads as joinable, each of which will execute the dot product
    * routine. Their offset into the global vectors is specified by passing
    * the "i" argument in pthread_create().
    */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (i = 0; i < NUMTHRDS; i++) {
        long *arg = malloc(sizeof(*arg));
        *arg = i;
        int rc = pthread_create(&threads[i], &attr, dotprod, (void *)arg);
        // get return code for checking error when creating thread
        if (rc) {
            fprintf(stderr, "Error: pthread_create() failed with code %d\n", rc);
            exit(EXIT_FAILURE);
        }
    } 

    pthread_attr_destroy(&attr);

    /* Wait on the threads for final result */
    pthread_attr_destroy(&attr);
    for (i = 0; i < NUMTHRDS; i++) {
        int rc = pthread_join(threads[i], &status);
        // get return code for checking error when joining thread
        if (rc) {
            fprintf(stderr, "Error: pthread_join() failed with code %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    /* After joining, print out the results and cleanup */
    printf ("Final Global Sum=%li\n",sum);
    free (a);
    free (b);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit(NULL);
}