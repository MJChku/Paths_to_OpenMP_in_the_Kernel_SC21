/*
 * pthread_barrier_wait.c
 */
#include "debug.h"
#include "pthread.h"
#include "implement.h"
#include "pthread_barrier_common.h"

int
pthread_barrier_wait (pthread_barrier_t * barrier)
{
    NK_PROFILE_ENTRY();
 
    if (barrier == NULL)
    {
      return EINVAL;
    }

    int res = 0;

    DEBUG("Thread (%p) entering barrier (%p)\n", (void*)get_cur_thread(), (void*)barrier);

    bspin_lock(&barrier->lock);

    if (--barrier->remaining == 0) {
        res = NK_BARRIER_LAST;
	res = PTHREAD_BARRIER_SERIAL_THREAD;
        atomic_cmpswap(barrier->notify, 0, 1);
    } else {
        bspin_unlock(&barrier->lock);
        BARRIER_WHILE(barrier->notify != 1);
    }

    DEBUG("Thread (%p) exiting barrier (%p)\n", (void*)get_cur_thread(), (void*)barrier);

    register unsigned init_count = barrier->init_count;

    if (atomic_inc_val(barrier->remaining) == init_count) {

        atomic_cmpswap(barrier->notify, 1, 0);
        bspin_unlock(&barrier->lock);
    }
    NK_PROFILE_EXIT();
    return res;

}
