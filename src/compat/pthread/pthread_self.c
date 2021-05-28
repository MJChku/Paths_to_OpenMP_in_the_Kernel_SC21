/*
 * pthread_self.c
 *
 */

/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <nautilus/nautilus.h>
#include "pthread.h"
#include "implement.h"

pthread_t
pthread_self (void)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function returns a reference to the current running
 *      thread.
 *
 * PARAMETERS
 *      N/A
 *
 *
 * DESCRIPTION
 *      This function returns a reference to the current running
 *      thread.
 *
 * RESULTS
 *              pthread_t       reference to the current thread
 *
 * ------------------------------------------------------
 */
{
  return get_cur_thread();
  
  //all below is not used
  /* NK_PROFILE_ENTRY(); */
  /* return get_cur_thread(); */
  /* pthread_t self; */
  /* pte_thread_t * sp; */

  /* sp = (pte_thread_t *) pthread_getspecific (pte_selfThreadKey); */

  /* if (sp != NULL) */
  /*   { */
  /*     self = sp->ptHandle; */
  /*   } */
  /* else */
  /*   { */
  /*     /\* */
  /*      * Need to create an implicit 'self' for the currently */
  /*      * executing thread. */
  /*      * */
  /*      * Note that this is a potential memory leak as there is */
  /*      * no way to free the memory and any resources allocated */
  /*      * by pte_new! */
  /*      *\/ */
  /*     self = pte_new (); */
  /*     sp = (pte_thread_t *) self.p; */

  /*     if (sp != NULL) */
  /*       { */
  /*         /\* */
  /*          * This is a non-POSIX thread which has chosen to call */
  /*          * a POSIX threads function for some reason. We assume that */
  /*          * it isn't joinable, but we do assume that it's */
  /*          * (deferred) cancelable. */
  /*          *\/ */
  /*         sp->implicit = 1; */
  /*         sp->detachState = PTHREAD_CREATE_DETACHED; */

  /*         sp->threadId = pte_osThreadGetHandle(); */
  /*         /\* */
  /*          * No need to explicitly serialise access to sched_priority */
  /*          * because the new handle is not yet public. */
  /*          *\/ */
  /*         sp->sched_priority = 0; */

  /*         pthread_setspecific (pte_selfThreadKey, (void *) sp); */
  /*       } */
  /*   } */

  /* NK_PROFILE_EXIT(); */
  /* return (self); */

}				/* pthread_self */
