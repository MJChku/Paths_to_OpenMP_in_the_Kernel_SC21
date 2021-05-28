#include "pthread.h"
#include "semaphore.h"
#include "implement.h"
#include "sem_common.h"

int
sem_trywait (sem_t * sem)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function tries to wait on a semaphore.
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 * DESCRIPTION
 *      This function tries to wait on a semaphore. If the
 *      semaphore value is greater than zero, it decreases
 *      its value by one. If the semaphore value is zero, then
 *      this function returns immediately with the error EAGAIN
 *
 * RESULTS
 *              0               successfully decreased semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EAGAIN          the semaphore was already locked,
 *              EINVAL          'sem' is not a valid semaphore,
 *              ENOTSUP         sem_trywait is not supported,
 *              EINTR           the function was interrupted by a signal,
 *              EDEADLK         a deadlock condition was detected.
 *
 * ------------------------------------------------------
 */
{
  if (sem == NULL)
    {
      return EINVAL;
    }
 NK_PROFILE_ENTRY();

 int result =  nk_semaphore_try_down(sem); 
 
 NK_PROFILE_EXIT();
 return result;

}				/* sem_trywait */
