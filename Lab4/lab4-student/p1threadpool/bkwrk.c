#include "bktpool.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/sched.h>
#include <sys/syscall.h>      /* Definition of SYS_* constants */
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>  // mmap

//#define DEBUG
#define INFO
//#define WORK_THREAD

#ifdef WORK_THREAD
static struct bkworker_t worker_array[MAX_WORKER];
static int wrkid_busy_array[MAX_WORKER];

struct bkworker_t *worker = worker_array;
int *wrkid_busy = wrkid_busy_array;

#else
// fork version dùng mmap hoặc malloc
struct bkworker_t *worker;
int *wrkid_busy;
#endif

void bkwrk_init_shared_memory() {
#ifndef WORK_THREAD
    // Shared memory for workers
    worker = mmap(NULL,
                  sizeof(struct bkworker_t) * MAX_WORKER,
                  PROT_READ | PROT_WRITE,
                  MAP_SHARED | MAP_ANONYMOUS,
                  -1, 0);
    if (worker == MAP_FAILED) {
        perror("mmap worker");
        exit(1);
    }

    // Shared memory for busy flags
    wrkid_busy = mmap(NULL,
                      sizeof(int) * MAX_WORKER,
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS,
                      -1, 0);
    if (wrkid_busy == MAP_FAILED) {
        perror("mmap wrkid_busy");
        exit(1);
    }

    job_arg = mmap(NULL,
                  sizeof(void *) * STACK_SIZE,
                  PROT_READ | PROT_WRITE,
                  MAP_SHARED | MAP_ANONYMOUS,
                  -1, 0);
    if (job_arg == MAP_FAILED) {
        perror("mmap job_arg");
        exit(1);
    }

    // Initialize
    for (int i = 0; i < MAX_WORKER; ++i) {
        wrkid_busy[i] = 0;
        worker[i].func = NULL;
        worker[i].arg = NULL;
        worker[i].bktaskid = -1;
        worker[i].arg_int = 0;
    }
#endif
}

/*
 * FIFO queue to track free workers
 */
static int free_queue[MAX_WORKER];
static int fq_head = 0, fq_tail = 0, fq_count = 0;
static pthread_mutex_t fq_mutex = PTHREAD_MUTEX_INITIALIZER;

// mutex để serialize tất cả các printf/fprintf
static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Initialize FIFO with all worker IDs */
static void bkwrk_init_fifo(void) {
    pthread_mutex_lock(&fq_mutex);
    fq_head = fq_tail = fq_count = 0;
    for (int i = 0; i < MAX_WORKER; i++) {
        free_queue[fq_tail++] = i;
        fq_count++;
    }
    pthread_mutex_unlock(&fq_mutex);
}

/* Release a worker back into FIFO */
void bkwrk_release_worker(int wrkid) {
    pthread_mutex_lock(&fq_mutex);
    free_queue[fq_tail++] = wrkid;
    fq_tail %= MAX_WORKER;
    fq_count++;
    pthread_mutex_unlock(&fq_mutex);

    // debug
    // pthread_mutex_lock(&print_mutex);
    // fprintf(stderr, "[DEBUG release_worker] wrkid=%d head=%d tail=%d count=%d\n",
    //         wrkid, fq_head, fq_tail, fq_count);
    // pthread_mutex_unlock(&print_mutex);
}

void * bkwrk_worker(void * arg) {
    sigset_t set;
    int sig, s;
    int i = * ( (int *) arg );
    struct bkworker_t *wrk = &worker[i];

    if (wrk->func) {
        fprintf(stderr, "worker %i already has a task!\n", i);
        return NULL;
    }

    /* Taking the mask for waking up */
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGQUIT);

#ifdef DEBUG
    fprintf(stderr, "worker %i start (pid=%d)\n", i, getpid());
    fflush(stderr);
#endif
    while (1) {
        sigset_t current;
        sigprocmask(SIG_SETMASK, NULL, &current);
        if (!sigismember(&current, SIGUSR1)) {
            fprintf(stderr, "SIGUSR1 is not blocked! sigwait will not work!\n");
        }
        s = sigwait(&set, &sig);
        if (s != 0) continue;
        fprintf(stderr, "worker %i wake up\n", i);

        if (wrk->func) {
            /* Call the function */
            if (wrk->arg) {
                wrk->func(&wrk->arg_int);
            }
        }

        /* done */
        wrkid_busy[i] = 0;
        worker[i].func     = NULL;
        worker[i].arg      = NULL;
        worker[i].bktaskid = -1;
        bkwrk_release_worker(i);
    }
}

int bktask_assign_worker(unsigned int bktaskid, unsigned int wrkid) {
    if (wrkid >= MAX_WORKER) return -1;
    struct bktask_t *tsk = bktask_get_byid(bktaskid);
    if (!tsk) return -1;

    wrkid_busy[wrkid]          = 1;
    worker[wrkid].func         = tsk->func;
    worker[wrkid].arg          = tsk->arg;
    worker[wrkid].bktaskid     = bktaskid;
    worker[wrkid].arg_int      = *( (int *) tsk->arg );

    pthread_mutex_lock(&print_mutex);
    printf("Assign tsk %u to wrk %u\n", tsk->bktaskid, wrkid);
    pthread_mutex_unlock(&print_mutex);

    return 0;
}

int bkwrk_create_worker() {
    unsigned int i;
    bkwrk_init_fifo();

    for (i = 0; i < MAX_WORKER; i++) {
#ifdef WORK_THREAD
        void ** child_stack = malloc(STACK_SIZE);
        unsigned int wrkid = i;
        sigset_t set;

        sigemptyset(&set);
        sigaddset(&set, SIGQUIT);
        sigaddset(&set, SIGUSR1);
        sigprocmask(SIG_BLOCK, &set, NULL);

        void *stack_top = child_stack + STACK_SIZE;
        wrkid_tid[i] = clone(&bkwrk_worker, stack_top,
                             CLONE_VM | CLONE_FILES,
                             &wrkid);
#ifdef INFO
        fprintf(stderr, "bkwrk_create_worker thread[%u]=tid %u\n",
                i, wrkid_tid[i]);
#endif
        usleep(100);

#else
        // ─────── FORK-VERSION ───────────────────────────
        int wrkid = i;
        int *child_arg = malloc(sizeof(*child_arg));
        *child_arg = wrkid;
        
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGUSR1);
        sigaddset(&set, SIGQUIT);
        if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
            perror("sigprocmask block");
            exit(1);
        }
        pid_t pid = fork();
        // fprintf(stderr, "bkwrk_create_worker process[%u]=pid %u\n",
        //   wrkid, pid);
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Child process: unblock signals then run worker loop
            bkwrk_worker(child_arg);
            _exit(0);
        } else {
          // Parent: record child PID
          wrkid_tid[i] = pid;
          free(child_arg);
        }
        
#ifdef INFO
        fprintf(stderr, "bkwrk_create_worker process[%u]=pid %u\n",
                i, wrkid_tid[i]);
#endif
        usleep(100);
        // ───────────────────────────────────────────────────
#endif
    }

    return 0;
}

int bkwrk_get_worker() {
    pthread_mutex_lock(&fq_mutex);
    if (fq_count == 0) {
        pthread_mutex_unlock(&fq_mutex);
        return -1;
    }
    int wrkid = free_queue[fq_head++];
    fq_head %= MAX_WORKER;
    fq_count--;
    pthread_mutex_unlock(&fq_mutex);
    return wrkid;
}

int bkwrk_dispatch_worker(unsigned int wrkid) {
#ifdef WORK_THREAD
    unsigned int tid = wrkid_tid[wrkid];
    if (!worker[wrkid].func) return -1;
#ifdef DEBUG
    pthread_mutex_lock(&print_mutex);
    fprintf(stderr, "dispatch thread wrkid=%u → tkill(%u)\n", wrkid, tid);
    pthread_mutex_unlock(&print_mutex);
#endif
    syscall(SYS_tkill, tid, SIG_DISPATCH);
#else
    // ─────── FORK-VERSION dispatch ────────────────
    pid_t pid = wrkid_tid[wrkid];
    if (kill(pid, SIG_DISPATCH) < 0)
        return -1;
    // ────────────────────────────────────────────────
#endif
    return 0;
}
