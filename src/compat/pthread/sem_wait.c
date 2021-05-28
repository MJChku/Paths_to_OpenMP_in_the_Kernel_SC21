#include <nautilus/nautilus.h>
#include "pthread.h"
#include "semaphore.h"
#include "implement.h"
#include "sem_common.h"


int
sem_wait (sem_t * sem)
{
     NK_PROFILE_ENTRY();
     nk_semaphore_down(sem);
     NK_PROFILE_EXIT();
     return 0;
}				/* sem_wait */


int
sem_wait_nocancel (sem_t * sem)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function  waits on a semaphore, and doesn't
 *      allow cancellation.
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 * DESCRIPTION
 *      This function waits on a semaphore. If the
 *      semaphore value is greater than zero, it decreases
 *      its value by one. If the semaphore value is zero, then
 *      the calling thread (or process) is blocked until it can
 *      successfully decrease the value or until interrupted by
 *      a signal.
 *
 * RESULTS
 *              0               successfully decreased semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EINVAL          'sem' is not a valid semaphore,
 *              ENOSYS          semaphores are not supported,
 *              EINTR           the function was interrupted by a signal,
 *              EDEADLK         a deadlock condition was detected.
 *
 * ------------------------------------------------------
 */
{
  NK_PROFILE_ENTRY();
  nk_semaphore_down(sem);
  NK_PROFILE_EXIT();
  return 0;

}				/* sem_wait_nocancel */
