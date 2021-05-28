
/*
 * pthread_cancel.c
 *
 */

#include "pthread.h"
#include "implement.h"
/* #include <stdio.h> */
#include <nautilus/nautilus.h>

static int thread_detach(nk_thread_t *t){
  
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
    if (t->refcount==0) { 
       nk_thread_destroy(t);
    }

    preempt_enable();

    return 0;
}

int
pthread_cancel (pthread_t thread)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function requests cancellation of 'thread'.
 *
 * PARAMETERS
 *      thread
 *              reference to an instance of pthread_t
 *
 *
 * DESCRIPTION
 *      This function requests cancellation of 'thread'.
 *      NOTE: cancellation is asynchronous; use pthread_join to
 *                wait for termination of 'thread' if necessary.
 *
 * RESULTS
 *              0               successfully requested cancellation,
 *              ESRCH           no thread found corresponding to 'thread',
 *              ENOMEM          implicit self thread create failed.
 * ------------------------------------------------------
 */
{
  //thread_detach(thread);
  BOGUS();
  return -1;
  /* NK_PROFILE_ENTRY(); */
  /* int result; */
  /* int cancel_self; */
  /* pthread_t self; */
  /* pte_thread_t * tp; */

  /* result = pthread_kill (thread, 0); */

  /* if (0 != result) */
  /*   { */
  /*     return result; */
  /*   } */

  /* if ((self = pthread_self ()).p == NULL) */
  /*   { */
  /*     return ENOMEM; */
  /*   }; */

  /* /\* */
  /*  * FIXME!! */
  /*  * */
  /*  * Can a thread cancel itself? */
  /*  * */
  /*  * The standard doesn't */
  /*  * specify an error to be returned if the target */
  /*  * thread is itself. */
  /*  * */
  /*  * If it may, then we need to ensure that a thread can't */
  /*  * deadlock itself trying to cancel itself asyncronously */
  /*  * (pthread_cancel is required to be an async-cancel */
  /*  * safe function). */
  /*  *\/ */
  /* cancel_self = pthread_equal (thread, self); */

  /* tp = (pte_thread_t *) thread.p; */

  /* /\* */
  /*  * Lock for async-cancel safety. */
  /*  *\/ */
  /* (void) pthread_mutex_lock (&tp->cancelLock); */

  /* if (tp->cancelType == PTHREAD_CANCEL_ASYNCHRONOUS */
  /*     && tp->cancelState == PTHREAD_CANCEL_ENABLE */
  /*     && tp->state < PThreadStateCanceling) */
  /*   { */
  /*     if (cancel_self) */
  /*       { */
  /*         tp->state = PThreadStateCanceling; */
  /*         tp->cancelState = PTHREAD_CANCEL_DISABLE; */

  /*         (void) pthread_mutex_unlock (&tp->cancelLock); */
  /*         pte_throw (PTE_EPS_CANCEL); */

  /*         /\* Never reached *\/ */
  /*       } */
  /*     else */
  /*       { */
  /*         /\* */
  /*          * We don't support asynchronous cancellation for thread other than ourselves. */
  /*          * as it requires significant platform and OS specific functionality (see below). */
  /*          * */
  /*          * We should never get here, as we don't allow the cancellability type to be */
  /*          * sent to async. */
  /*          * */
  /*          * If you really wanted to implement async cancellation, you would probably need to */
  /*          * do something like the Win32 implement did, which is: */
  /*          *   1. Suspend the target thread. */
  /*          *   2. Replace the PC for the target thread to a routine that throws an exception */
  /*          *      or does a longjmp, depending on cleanup method. */
  /*          *   3. Resume the target thread. */
  /*          * */
  /*          * Note that most of the async cancellation code is still in here if anyone */
  /*          * wanted to add the OS/platform specific stuff. */
  /*          *\/ */
  /*         (void) pthread_mutex_unlock (&tp->cancelLock); */

  /*         result = EPERM; */

  /*       } */
  /*   } */
  /* else */
  /*   { */
  /*     /\* */
  /*      * Set for deferred cancellation. */
  /*      *\/ */
  /*     if (tp->state < PThreadStateCancelPending) */
  /*       { */
  /*         tp->state = PThreadStateCancelPending; */

  /*         if (pte_osThreadCancel(tp->threadId) != PTE_OS_OK) */
  /*           { */
  /*             result = ESRCH; */
  /*           } */
  /*       } */
  /*     else if (tp->state >= PThreadStateCanceling) */
  /*       { */
  /*         result = ESRCH; */
  /*       } */

  /*     (void) pthread_mutex_unlock (&tp->cancelLock); */
  /*   } */

  /* NK_PROFILE_EXIT(); */
  /* return (result); */
}
