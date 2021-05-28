/*
 * pthread_detach.c
 */

#include "nk/pte_osal.h"

#include "pthread.h"
#include "implement.h"

int
pthread_detach (pthread_t thread)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function detaches the given thread.
 *
 * PARAMETERS
 *      thread
 *              an instance of a pthread_t
 *
 *
 * DESCRIPTION
 *      This function detaches the given thread. You may use it to
 *      detach the main thread or to detach a joinable thread.
 *      NOTE:   detached threads cannot be joined;
 *              storage is freed immediately on termination.
 *
 * RESULTS
 *              0               successfully detached the thread,
 *              EINVAL          thread is not a joinable thread,
 *              ENOSPC          a required resource has been exhausted,
 *              ESRCH           no thread could be found for 'thread',
 *
 * ------------------------------------------------------
 */
{
    nk_thread_t * t = (nk_thread_t*) thread;
    preempt_disable();

    ASSERT(t->refcount > 0);

    /* remove me from my parent's child list */
    list_del(&(t->child_node));

    --t->refcount;

    // conditional reaping is done by the scheduler when threads are created
    // this makes the join+exit path much faster in the common case and 
    // bulks reaping events together
    // the user can also explictly reap when needed
    // plus the autoreaper thread can be enabled 
    // the following code can be enabled if you want to reap immediately once
    // a thread's refcount drops to zero
    // 
    //if (t->refcount==0) { 
    //   nk_thread_destroy(t);
    //}

    preempt_enable();

    return 0;


  /* NK_PROFILE_ENTRY(); */
  /* int result; */
  /* unsigned char destroyIt = PTE_FALSE; */
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
  /*     /\* */
  /*      * Joinable pte_thread_t structs are not scavenged until */
  /*      * a join or detach is done. The thread may have exited already, */
  /*      * but all of the state and locks etc are still there. */
  /*      *\/ */
  /*     result = 0; */

  /*     if (pthread_mutex_lock (&tp->cancelLock) == 0) */
  /*       { */
  /*         if (tp->state != PThreadStateLast) */
  /*           { */
  /*             tp->detachState = PTHREAD_CREATE_DETACHED; */
  /*           } */
  /*         else if (tp->detachState != PTHREAD_CREATE_DETACHED) */
  /*           { */
  /*             /\* */
  /*              * Thread is joinable and has exited or is exiting. */
  /*              *\/ */
  /*             destroyIt = PTE_TRUE; */
  /*           } */
  /*         (void) pthread_mutex_unlock (&tp->cancelLock); */
  /*       } */
  /*     else */
  /*       { */
  /*         /\* cancelLock shouldn't fail, but if it does ... *\/ */
  /*         result = ESRCH; */
  /*       } */
  /*   } */

  /* pte_osMutexUnlock(pte_thread_reuse_lock); */

  /* if (result == 0) */
  /*   { */
  /*     /\* Thread is joinable *\/ */

  /*     if (destroyIt) */
  /*       { */
  /*         /\* The thread has exited or is exiting but has not been joined or */
  /*          * detached. Need to wait in case it's still exiting. */
  /*          *\/ */
  /* 	  pte_osThreadWaitForEnd(tp->threadId); */

  /*         pte_threadDestroy (thread); */
  /*       } */
  /*   } */

  /* NK_PROFILE_EXIT(); */
  /* return (result); */

}				/* pthread_detach */
