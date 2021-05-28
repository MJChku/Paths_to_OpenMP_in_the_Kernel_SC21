/*
 * pthread_testcancel.c
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include "pthread.h"
#include "implement.h"


void
pthread_testcancel (void)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function creates a deferred cancellation point
 *      in the calling thread. The call has no effect if the
 *      current cancelability state is
 *              PTHREAD_CANCEL_DISABLE
 *
 * PARAMETERS
 *      N/A
 *
 *
 * DESCRIPTION
 *      This function creates a deferred cancellation point
 *      in the calling thread. The call has no effect if the
 *      current cancelability state is
 *              PTHREAD_CANCEL_DISABLE
 *
 *      NOTES:
 *      1)      Cancellation is asynchronous. Use pthread_join
 *              to wait for termination of thread if necessary
 *
 * RESULTS
 *              N/A
 *
 * ------------------------------------------------------
 */
{
  BOGUS();
  return ;
  /* NK_PROFILE_ENTRY(); */
  /* pthread_t self = pthread_self (); */
  /* pte_thread_t * sp = (pte_thread_t *) self.p; */

  /* if (sp == NULL) */
  /*   { */
  /*     return; */
  /*   } */

  /* /\* */
  /*  * Pthread_cancel() will have set sp->state to PThreadStateCancelPending */
  /*  * and set an event, so no need to enter kernel space if */
  /*  * sp->state != PThreadStateCancelPending - that only slows us down. */
  /*  *\/ */
  /* if (sp->state != PThreadStateCancelPending) */
  /*   { */
  /*     return; */
  /*   } */

  /* (void) pthread_mutex_lock (&sp->cancelLock); */

  /* if (sp->cancelState != PTHREAD_CANCEL_DISABLE) */
  /*   { */
  /*     sp->state = PThreadStateCanceling; */
  /*     sp->cancelState = PTHREAD_CANCEL_DISABLE; */

  /*     (void) pthread_mutex_unlock (&sp->cancelLock); */
  /*     pte_throw (PTE_EPS_CANCEL); */
  /*   } */

  /* (void) pthread_mutex_unlock (&sp->cancelLock); */
  /* NK_PROFILE_EXIT(); */
}				/* pthread_testcancel */
