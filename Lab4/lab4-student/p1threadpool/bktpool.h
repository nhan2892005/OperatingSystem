#ifndef BKTPOOL_H
#define BKTPOOL_H

#include <stdlib.h>

#include <pthread.h>

#define MAX_WORKER 10
#define WRK_THREAD 1
#define STACK_SIZE 4096
#define SIG_DISPATCH SIGUSR1

/* Task ID is unique non-decreasing integer */
int taskid_seed;

int wrkid_tid[MAX_WORKER];
int* wrkid_busy;
int wrkid_cur;

struct bktask_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int bktaskid;
  struct bktask_t * tnext;
}* bktask;

int bktask_sz;

struct bkworker_t {
  void( * func)(void * arg);
  void * arg;
  unsigned int wrkid;
  unsigned int bktaskid;
  unsigned int arg_int;
};

struct bkworker_t *worker;
void **job_arg;

/* Prototype API */
void bkwrk_init_shared_memory();

/* bktpool module */
int bktpool_init();

/* bktask module */
struct bktask_t * bktask_get_byid(unsigned int bktaskid);
int bktask_init(unsigned int * bktaskid, void * func, void * arg);
int bktask_assign_worker(unsigned int bktaskid, unsigned int wrkid);

/* bkwrk module */
void * bkwrk_worker(void * arg);
int bkwrk_create_worker();
int bkwrk_dispatch_worker(unsigned int wrkid);
int bkwrk_get_worker();

#endif