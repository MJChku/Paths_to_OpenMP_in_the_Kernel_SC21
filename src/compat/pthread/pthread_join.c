/*
 * pthread_join.c
*/
#include "nk/pte_osal.h"
#include <nautilus/nautilus.h>
#include "pthread.h"
#include "implement.h"

//#include <stdio.h>

int
pthread_join (pthread_t thread, void **value_ptr)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function waits for 'thread' to terminate and
 *      returns the thread's exit value if 'value_ptr' is not
 *      NULL. This also detaches the thread on successful
 *      completion.
 *
 * PARAMETERS
 *      thread
 *              an instance of pthread_t
 *
 *      value_ptr
 *              pointer to an instance of pointer to void
 *
 *
 * DESCRIPTION
 *      This function waits for 'thread' to terminate and
 *      returns the thread's exit value if 'value_ptr' is not
 *      NULL. This also detaches the thread on successful
 *      completion.
 *      NOTE:   detached threads cannot be joined or canceled
 *
 * RESULTS
 *              0               'thread' has completed
 *              EINVAL          thread is not a joinable thread,
 *              ESRCH           no thread could be found with ID 'thread',
 *              ENOENT          thread couldn't find it's own valid handle,
 *              EDEADLK         attempt to join thread with self
 *
 * ------------------------------------------------------
 */
{

  return nk_join(thread, value_ptr);

  nk_thread_t * thethread = (nk_thread_t *) thread;
  
  if(thethread->parent == get_cur_thread()){
     return nk_join(thread, value_ptr);
  }else{
     return 0;
  }

  //return nk_join(thread, value_ptr);
  /* NK_PROFILE_ENTRY(); */
  /* int result; */
  /* pthread_t self; */
  /* pte_thread_t * tp = (pte_thread_t *) thread.p; */


  /* pte_osMutexLock (pte_thread_reuse_lock); */

  /* if (NULL == tp */
  /*     || thread.x != tp->ptHandle.x) */
  /*   { */
  /*     result = ESRCH; */
  /*   } */
  /* else if (PTHREAD_CREATE_DETACHED == tp->detachState) */
  /*   { */
  /*     result = EINVAL; */
  /*   } */
  /* else */
  /*   { */
  /*     result = 0; */
  /*   } */

  /* pte_osMutexUnlock(pte_thread_reuse_lock); */

  /* if (result == 0) */
  /*   { */
  /*     /\* */
  /*      * The target thread is joinable and can't be reused before we join it. */
  /*      *\/ */
  /*     self = pthread_self(); */

  /*     if (NULL == self.p) */
  /*       { */
  /*         result = ENOENT; */
  /*       } */
  /*     else if (pthread_equal (self, thread)) */
  /*       { */
  /*         result = EDEADLK; */
  /*       } */
  /*     else */
  /*       { */
  /*         /\* */
  /*          * Pthread_join is a cancelation point. */
  /*          * If we are canceled then our target thread must not be */
  /*          * detached (destroyed). This is guarranteed because */
  /*          * pthreadCancelableWait will not return if we */
  /*          * are canceled. */
  /*          *\/ */

  /*         result = pte_osThreadWaitForEnd(tp->threadId); */

  /*         if (PTE_OS_OK == result) */
  /*           { */
  /*             if (value_ptr != NULL) */
  /*               { */
  /*                 *value_ptr = tp->exitStatus; */
  /*               } */

  /*             /\* */
  /*              * The result of making multiple simultaneous calls to */
  /*              * pthread_join() or pthread_detach() specifying the same */
  /*              * target is undefined. */
  /*              *\/ */

  /* 	      //mjc detached already */
  /*             //result = pthread_detach (thread); */
  /*           } */
  /* 	  else if (result == PTE_OS_INTERRUPTED) */
  /* 	    { */
  /* 	      /\* Call was cancelled, but still return success (per spec) *\/ */
  /* 	      result = 0; */
  /* 	    } */
  /*         else */
  /*           { */
  /*             result = ESRCH; */
  /*           } */
  /*       } */
  /*   } */

  /* NK_PROFILE_EXIT(); */
  /* return (result); */

}				/* pthread_join */
