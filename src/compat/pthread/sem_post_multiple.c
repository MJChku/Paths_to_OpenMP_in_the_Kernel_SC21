#include <nautilus/nautilus.h>
#include "pthread.h"
#include "semaphore.h"
#include "implement.h"
#include "sem_common.h"

int
sem_post_multiple (sem_t * sem, int count)
{
  NK_PROFILE_ENTRY();
  while( count--){
    if(nk_wait_queue_empty(sem->wait_queue)){
       break;
    }
    nk_semaphore_up(sem);
  }
  NK_PROFILE_EXIT();
  return 0;
}				/* sem_post_multiple */
