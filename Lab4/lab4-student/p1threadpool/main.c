#include <stdio.h>
#include "bktpool.h"
#undef STRESS_TEST

int func(void * arg) {
  int id = * ((int * ) arg);

  printf("Task func - Hello from %d\n", id);
  fflush(stdout);

  return 0;
}

int main(int argc, char * argv[]) {
  int tid[15];
  int wid[15];
  int id[15];
  int ret;

  taskid_seed = 0;
  wrkid_cur = 0;
  bktask_sz = 0;

  ret = bktpool_init();

  if (ret != 0)
    return -1;

  id[0] = 1;
  bktask_init( & tid[0], & func, (void * ) & id[0]);
  id[1] = 2;
  bktask_init( & tid[1], & func, (void * ) & id[1]);
  id[2] = 5;
  bktask_init( & tid[2], & func, (void * ) & id[2]);

  wid[1] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[0], wid[1]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[0], wid[1]);

  bkwrk_dispatch_worker(wid[1]);

  wid[0] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[1], wid[0]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[1], wid[0]);

  wid[2] = bkwrk_get_worker();
  ret = bktask_assign_worker(tid[2], wid[2]);
  if (ret != 0)
    printf("assign_task_failed tid=%d wid=%d\n", tid[2], wid[2]);

  bkwrk_dispatch_worker(wid[0]);
  bkwrk_dispatch_worker(wid[2]);

  fflush(stdout);
  sleep(1);

#ifdef STRESS_TEST
  int i = 0;
  for (i = 0; i < 15; i++) {
    id[i] = i;
    bktask_init( & tid[i], & func, (void * ) & id[i]);

    wid[i] = bkwrk_get_worker();
    ret = bktask_assign_worker(tid[i], wid[i]);

    if (ret != 0)
      printf("assign_task_failed tid=%d wid=%d\n", tid[i], wid[i]);

    bkwrk_dispatch_worker(wid[i]);
  }

  sleep(3);
#endif

  return 0;
}