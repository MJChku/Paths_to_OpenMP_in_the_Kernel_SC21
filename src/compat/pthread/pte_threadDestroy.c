/*
 * pte_threadDestroy.c
 *
 * Description:
 * This translation unit implements routines which are private to
 * the implementation and may be used throughout it.
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
 *      Based upon Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 *
 *      Contact Email: rpj@callisto.canberra.edu.au
 *
 *      The original list of contributors to the Pthreads-win32 project
 *      is contained in the file CONTRIBUTORS.ptw32 included with the
 *      source code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
#include <nautilus/nautilus.h>
#include <nautilus/naut_string.h>
#include "pthread.h"
#include "implement.h"



static void
pte_threadDestroyCommon (pthread_t thread, unsigned char shouldThreadExit)
{
  NK_PROFILE_ENTRY();
  pte_thread_t * tp = (pte_thread_t *) thread.p;
  pte_thread_t threadCopy;

  if (tp != NULL)
    {
      /*
       * Copy thread state so that the thread can be atomically NULLed.
       */
      memcpy (&threadCopy, tp, sizeof (threadCopy));

      /*
       * Thread ID structs are never freed. They're NULLed and reused.
       * This also sets the thread to PThreadStateInitial (invalid).
       */
      pte_threadReusePush (thread);

      (void) pthread_mutex_destroy(&threadCopy.cancelLock);
      (void) pthread_mutex_destroy(&threadCopy.threadLock);

      if (threadCopy.threadId != 0)
        {
          if (shouldThreadExit)
            {
              pte_osThreadExitAndDelete(threadCopy.threadId);
            }
          else
            {
              pte_osThreadDelete(threadCopy.threadId);
            }
        }



    }
  NK_PROFILE_EXIT();
}				/* pte_threadDestroy */

void pte_threadDestroy (pthread_t thread)
{
  pte_threadDestroyCommon(thread,0);
}

void pte_threadExitAndDestroy (pthread_t thread)
{
  pte_threadDestroyCommon(thread,1);
}

