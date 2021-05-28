/*
 * pthread_kill.c
 */

/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
#include <nautilus/nautilus.h>
#include <nautilus/naut_string.h>
#include "pthread.h"
#include "implement.h"

int
pthread_kill (pthread_t thread, int sig)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function requests that a signal be delivered to the
 *      specified thread. If sig is zero, error checking is
 *      performed but no signal is actually sent such that this
 *      function can be used to check for a valid thread ID.
 *
 * PARAMETERS
 *      thread  reference to an instances of pthread_t
 *      sig     signal. Currently only a value of 0 is supported.
 *
 *
 * DESCRIPTION
 *      This function requests that a signal be delivered to the
 *      specified thread. If sig is zero, error checking is
 *      performed but no signal is actually sent such that this
 *      function can be used to check for a valid thread ID.
 *
 * RESULTS
 *              ESRCH           the thread is not a valid thread ID,
 *              EINVAL          the value of the signal is invalid
 *                              or unsupported.
 *              0               the signal was successfully sent.
 *
 * ------------------------------------------------------
 */
{
  BOGUS();
  int result = 0;
  
  /* pte_thread_t * tp; */


  /* pte_osMutexLock (pte_thread_reuse_lock); */

  /* tp = (pte_thread_t *) thread.p; */

  /* if (NULL == tp */
  /*     || thread.x != tp->ptHandle.x */
  /*     || 0 == tp->threadId) */
  /*   { */
  /*     result = ESRCH; */
  /*   } */

  /* pte_osMutexUnlock(pte_thread_reuse_lock); */
  if (thread == NULL){
    result = ESRCH;
  }
  if (0 == result && 0 != sig)
    {
      /*
       * Currently does not support any signals.
       */
      result = EINVAL;
    }

  return result;

}				/* pthread_kill */
