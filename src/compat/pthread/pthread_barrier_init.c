
/*
 * pthread_barrier_init.c
 */
#include "debug.h"
#include <nautilus/nautilus.h>
#include "pthread.h"
#include "implement.h"
#include "pthread_barrier_common.h"
int
pthread_barrier_init (pthread_barrier_t * barrier,
                      const pthread_barrierattr_t * attr, unsigned int count)
{
    NK_PROFILE_ENTRY();
    
    int ret = 0;
    memset(barrier, 0, sizeof(pthread_barrier_t));
    barrier->lock = 0;

    if (unlikely(count == 0)) {
        ERROR("Barrier count must be greater than 0\n");
	NK_PROFILE_EXIT();
        return EINVAL;
    }

    DEBUG("Initializing barier, barrier at %p, count=%u\n", (void*)barrier, count);
    barrier->init_count = count;
    barrier->remaining  = count;
    barrier->pshared = (attr != NULL && *attr != NULL
                    ? (*attr)->pshared : PTHREAD_PROCESS_PRIVATE);

    NK_PROFILE_EXIT();
    return 0;	
	
}	
	
	
	
	
	
	
	
