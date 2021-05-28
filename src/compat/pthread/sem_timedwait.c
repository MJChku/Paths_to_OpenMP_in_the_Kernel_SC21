#include <nautilus/nautilus.h>
#include "pthread.h"
#include "semaphore.h"
#include "implement.h"
#include "sem_common.h"


int
sem_timedwait (sem_t * sem, const struct timespec *abstime)
{
   uint64_t timeout_ns = abstime->tv_sec*1000000000ULL+abstime->tv_nsec;
   int result  = nk_semaphore_down_timeout(sem, timeout_ns);
   return result;

}				/* sem_timedwait */
