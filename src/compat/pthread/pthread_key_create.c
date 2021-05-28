/*
 * pthread_key_create.c
 *
 */

/* #include <stdlib.h> */
#include <nautilus/nautilus.h>
#include "nk/pte_osal.h"

#include "pthread.h"
#include "implement.h"


int
pthread_key_create (pthread_key_t * key, void (*destructor) (void *))
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function creates a thread-specific data key visible
 *      to all threads. All existing and new threads have a value
 *      NULL for key until set using pthread_setspecific. When any
 *      thread with a non-NULL value for key terminates, 'destructor'
 *      is called with key's current value for that thread.
 *
 * PARAMETERS
 *      key
 *              pointer to an instance of pthread_key_t
 *
 *
 * DESCRIPTION
 *      This function creates a thread-specific data key visible
 *      to all threads. All existing and new threads have a value
 *      NULL for key until set using pthread_setspecific. When any
 *      thread with a non-NULL value for key terminates, 'destructor'
 *      is called with key's current value for that thread.
 *
 * RESULTS
 *              0               successfully created semaphore,
 *              EAGAIN          insufficient resources or PTHREAD_KEYS_MAX
 *                              exceeded,
 *              ENOMEM          insufficient memory to create the key,
 *
 * ------------------------------------------------------
 */
{
  return nk_tls_key_create(key, destructor); 
  /* NK_PROFILE_ENTRY(); */
  

  /* int result = 0; */
  /* pthread_key_t newkey; */

  /* if ((newkey = (pthread_key_t) calloc (1, sizeof (*newkey))) == NULL) */
  /*   { */
  /*     result = ENOMEM; */
  /*   } */
  /* else */
  /*   { */
  /*     memset(newkey,0,1*sizeof(*newkey)); */
  /*     pte_osResult osResult = pte_osTlsAlloc(&(newkey->key)); */

  /*     if (osResult != PTE_OS_OK) */
  /*       { */
  /*         result = EAGAIN; */

  /*         free (newkey); */
  /*         newkey = NULL; */
  /*       } */
  /*     else if (destructor != NULL) */
  /*       { */
  /*         /\* */
  /*          * Have to manage associations between thread and key; */
  /*          * Therefore, need a lock that allows multiple threads */
  /*          * to gain exclusive access to the key->threads list. */
  /*          * */
  /*          * The mutex will only be created when it is first locked. */
  /*          *\/ */
  /*         newkey->keyLock = PTHREAD_MUTEX_INITIALIZER; */
  /*         newkey->destructor = destructor; */
  /*       } */

  /*   } */

  /* *key = newkey; */

  /* NK_PROFILE_EXIT(); */
  /* return (result); */
}
