#include <nautilus/nautilus.h>
#include "nk/pte_osal.h"

#include "pthread.h"
#include "semaphore.h"
#include "implement.h"


int
sem_destroy (sem_t * sem)
{
  nk_semaphore_release(sem); 
  return 0;

}				/* sem_destroy */
