/*
 * pthread_exit.c
 *
 */

#include "pthread.h"
#include "implement.h"

void
pthread_exit (void *value_ptr)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function terminates the calling thread, returning
 *      the value 'value_ptr' to any joining thread.
 *
 * PARAMETERS
 *      value_ptr
 *              a generic data value (i.e. not the address of a value)
 *
 *
 * DESCRIPTION
 *      This function terminates the calling thread, returning
 *      the value 'value_ptr' to any joining thread.
 *      NOTE: thread should be joinable.
 *
 * RESULTS
 *              N/A
 *
 * ------------------------------------------------------
 */
{
  nk_thread_exit(value_ptr);
  
  /* pte_thread_t * sp; */

  /* /\* */
  /*  * Don't use pthread_self() to avoid creating an implicit POSIX thread handle */
  /*  * unnecessarily. */
  /*  *\/ */
  /* sp = (pte_thread_t *) pthread_getspecific (pte_selfThreadKey); */

  /* if (NULL == sp) */
  /*   { */
  /*     /\* */
  /*      * A POSIX thread handle was never created. I.e. this is a */
  /*      * Win32 thread that has never called a pthreads-win32 routine that */
  /*      * required a POSIX handle. */
  /*      * */
  /*      * Implicit POSIX handles are cleaned up in pte_throw() now. */
  /*      *\/ */

  /*     /\* Terminate thread *\/ */
  /*     pte_osThreadExit(); */

  /*     /\* Never reached *\/ */
  /*   } */

  /* sp->exitStatus = value_ptr; */

  /* pte_throw (PTE_EPS_EXIT); */

  /* /\* Never reached. *\/ */

}
