#include "pthread.h"
#include "semaphore.h"
#include "implement.h"
#include "sem_common.h"

int
sem_getvalue (sem_t * sem, int *sval)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function stores the current count value of the
 *      semaphore.
 * RESULTS
 *
 * Return value
 *
 *       0                  sval has been set.
 *      -1                  failed, error in errno
 *
 *  in global errno
 *
 *      EINVAL              'sem' is not a valid semaphore,
 *      ENOSYS              this function is not supported,
 *
 *
 * PARAMETERS
 *
 *      sem                 pointer to an instance of sem_t
 *
 *      sval                pointer to int.
 *
 * DESCRIPTION
 *      This function stores the current count value of the semaphore
 *      pointed to by sem in the int pointed to by sval.
 */
{
  if (sem == NULL ||  sval == NULL)
    {
      errno = EINVAL;
      return -1;
    }
  else
    {
      spin_lock(&(sem->lock));
      int value = sem->count;
      spin_unlock(&(sem->lock));
      *sval = value;
      return 0;
    }

}				/* sem_getvalue */
