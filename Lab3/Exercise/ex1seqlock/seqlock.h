#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock { /* TODO: implement the structure */
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   /* TODO: ... */
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */

    return 0;
}


static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */

    return 0;
}

