/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_THREAD_WINDOWS

/* Win32 thread management routines for SDL */

#include "../../SDL_hints.h"
#include "../../SDL_thread.h"
#include "../SDL_thread_c.h"
#include "../SDL_systhread.h"
#include "SDL_systhread_c.h"

#ifndef SDL_PASSED_BEGINTHREAD_ENDTHREAD
/* We'll use the C library from this DLL */
#include <process.h>

#ifndef STACK_SIZE_PARAM_IS_A_RESERVATION
#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000
#endif

/* Cygwin gcc-3 ... MingW64 (even with a i386 host) does this like MSVC. */
#if (defined(__MINGW32__) && (__GNUC__ < 4))
typedef unsigned long (__cdecl *pfnSDL_CurrentBeginThread) (void *, unsigned,
        unsigned (__stdcall *func)(void *), void *arg,
        unsigned, unsigned *threadID);
typedef void (__cdecl *pfnSDL_CurrentEndThread)(unsigned code);

#elif defined(__WATCOMC__)
/* This is for Watcom targets except OS2 */
#if __WATCOMC__ < 1240
#define __watcall
#endif
typedef unsigned long (__watcall * pfnSDL_CurrentBeginThread) (void *,
                                                               unsigned,
                                                               unsigned
                                                               (__stdcall *
                                                                func) (void
                                                                       *),
                                                               void *arg,
                                                               unsigned,
                                                               unsigned
                                                               *threadID);
typedef void (__watcall * pfnSDL_CurrentEndThread) (unsigned code);

#else
typedef uintptr_t(__cdecl * pfnSDL_CurrentBeginThread) (void *, unsigned,
                                                        unsigned (__stdcall *
                                                                  func) (void
                                                                         *),
                                                        void *arg, unsigned,
                                                        unsigned *threadID);
typedef void (__cdecl * pfnSDL_CurrentEndThread) (unsigned code);
#endif
#endif /* !SDL_PASSED_BEGINTHREAD_ENDTHREAD */


typedef struct ThreadStartParms
{
    void *args;
    pfnSDL_CurrentEndThread pfnCurrentEndThread;
} tThreadStartParms, *pThreadStartParms;

static DWORD
RunThread(void *data)
{
    pThreadStartParms pThreadParms = (pThreadStartParms) data;
    pfnSDL_CurrentEndThread pfnEndThread = pThreadParms->pfnCurrentEndThread;
    void *args = pThreadParms->args;
    SDL_free(pThreadParms);
    SDL_RunThread(args);
    if (pfnEndThread != NULL)
        pfnEndThread(0);
    return (0);
}

static DWORD WINAPI
RunThreadViaCreateThread(LPVOID data)
{
  return RunThread(data);
}

static unsigned __stdcall
RunThreadViaBeginThreadEx(void *data)
{
  return (unsigned) RunThread(data);
}

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args,
                     pfnSDL_CurrentBeginThread pfnBeginThread,
                     pfnSDL_CurrentEndThread pfnEndThread)
{
#elif defined(__CYGWIN__) || defined(__WINRT__)
int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args)
{
    pfnSDL_CurrentBeginThread pfnBeginThread = NULL;
    pfnSDL_CurrentEndThread pfnEndThread = NULL;
#else
int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args)
{
    pfnSDL_CurrentBeginThread pfnBeginThread = (pfnSDL_CurrentBeginThread)_beginthreadex;
    pfnSDL_CurrentEndThread pfnEndThread = (pfnSDL_CurrentEndThread)_endthreadex;
#endif /* SDL_PASSED_BEGINTHREAD_ENDTHREAD */
    pThreadStartParms pThreadParms =
        (pThreadStartParms) SDL_malloc(sizeof(tThreadStartParms));
    const DWORD flags = thread->stacksize ? STACK_SIZE_PARAM_IS_A_RESERVATION : 0;
    if (!pThreadParms) {
        return SDL_OutOfMemory();
    }
    /* Save the function which we will have to call to clear the RTL of calling app! */
    pThreadParms->pfnCurrentEndThread = pfnEndThread;
    /* Also save the real parameters we have to pass to thread function */
    pThreadParms->args = args;

    /* thread->stacksize == 0 means "system default", same as win32 expects */
    if (pfnBeginThread) {
        unsigned threadid = 0;
        thread->handle = (SYS_ThreadHandle)
            ((size_t) pfnBeginThread(NULL, (unsigned int) thread->stacksize,
                                     RunThreadViaBeginThreadEx,
                                     pThreadParms, flags, &threadid));
    } else {
        DWORD threadid = 0;
        thread->handle = CreateThread(NULL, thread->stacksize,
                                      RunThreadViaCreateThread,
                                      pThreadParms, flags, &threadid);
    }
    if (thread->handle == NULL) {
        return SDL_SetError("Not enough resources to create thread");
    }
    return 0;
}

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; /* must be 0x1000 */
    LPCSTR szName; /* pointer to name (in user addr space) */
    DWORD dwThreadID; /* thread ID (-1=caller thread) */
    DWORD dwFlags; /* reserved for future use, must be zero */
} THREADNAME_INFO;
#pragma pack(pop)

void
SDL_SYS_SetupThread(const char *name)
{
    if ((name != NULL) && IsDebuggerPresent()) {
        THREADNAME_INFO inf;

        /* C# and friends will try to catch this Exception, let's avoid it. */
        if (SDL_GetHintBoolean(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, SDL_FALSE)) {
            return;
        }

        /* This magic tells the debugger to name a thread if it's listening. */
        SDL_zero(inf);
        inf.dwType = 0x1000;
        inf.szName = name;
        inf.dwThreadID = (DWORD) -1;
        inf.dwFlags = 0;

        /* The debugger catches this, renames the thread, continues on. */
        RaiseException(0x406D1388, 0, sizeof(inf) / sizeof(ULONG), (const ULONG_PTR*) &inf);
    }
}

SDL_threadID
SDL_ThreadID(void)
{
    return ((SDL_threadID) GetCurrentThreadId());
}

int
SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    int value;

    if (priority == SDL_THREAD_PRIORITY_LOW) {
        value = THREAD_PRIORITY_LOWEST;
    } else if (priority == SDL_THREAD_PRIORITY_HIGH) {
        value = THREAD_PRIORITY_HIGHEST;
    } else {
        value = THREAD_PRIORITY_NORMAL;
    }
    if (!SetThreadPriority(GetCurrentThread(), value)) {
        return WIN_SetError("SetThreadPriority()");
    }
    return 0;
}

void
SDL_SYS_WaitThread(SDL_Thread * thread)
{
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
}

void
SDL_SYS_DetachThread(SDL_Thread * thread)
{
    CloseHandle(thread->handle);
}

#endif /* SDL_THREAD_WINDOWS */

/* vi: set ts=4 sw=4 expandtab: */