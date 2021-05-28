
/*
 * pthread_barrier_destroy.c
 */

/* #include <stdlib.h> */
#include <nautilus/nautilus.h>
#include <nautilus/intrinsics.h>
#include "debug.h"
#include "pthread.h"
#include "implement.h"
#include "pthread_barrier_common.h"

int
pthread_barrier_destroy (pthread_barrier_t * barrier)
{
    int res;

    if (!barrier) {
        return EINVAL;
    }

    DEBUG("Destroying barrier (%p)\n", (void*)barrier);

    bspin_lock(&barrier->lock);

    if (likely(barrier->remaining == barrier->init_count)) {
        res = 0;
    } else {
        /* someone is still waiting at the barrier? */
        ERROR("Someone still waiting at barrier, cannot destroy\n");
        res = EINVAL;
    }
    bspin_unlock(&barrier->lock);

    return res;

}
