//! \file
#ifndef Y_RTLD_DSO_INCLUDED
#define Y_RTLD_DSO_INCLUDED 1

#include "y/system/platform.hpp"
#include "y/system/compiler.hpp"

#if defined(__cplusplus)
#define Y_DLL_EXTERN() extern "C" {
#define Y_DLL_FINISH() }
#define Y_DLL_CPROTO extern "C"
#else
#define Y_DLL_EXTERN() //!< init exporting zone
#define Y_DLL_FINISH() //!< quit exporting zone
#define Y_DLL_CPROTO   //!< for C function in C++ module
#endif


#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define Y_DLL_API
#define Y_EXPORT  __declspec(dllexport)
#endif

#if defined(Y_BSD)
#define Y_DLL_API
#define Y_EXPORT
#endif




//______________________________________________________________________________
//
// Specific Module Init/Quit
//______________________________________________________________________________



#if defined(Y_BSD)

#define Y_DLL_SETUP(ON_INIT,ON_QUIT)                      \
__attribute__((constructor)) void OnInit() { ON_INIT(); } \
__attribute__((destructor))  void OnQuit() { ON_QUIT(); }

#endif

#if defined(Y_WIN)

#define Y_DLL_SETUP(ON_INIT,ON_QUIT)                                                    \
Y_DLL_CPROTO BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved) \
{                                                                                       \
/**/    (void)hinstDLL;                                                                 \
/**/    (void)lpvReserved;                                                              \
/**/    switch( fdwReason )                                                             \
/**/      {                                                                             \
/**/        case DLL_PROCESS_ATTACH: ON_INIT(); break;                                  \
/**/        case DLL_PROCESS_DETACH: ON_QUIT(); break;                                  \
/**/      }                                                                             \
/**/    return TRUE;                                                                    \
}

/*
 case DLL_THREAD_ATTACH:   YACK_dll_flags=1; ON_INIT(); break;\
 case DLL_THREAD_DETACH:   YACK_dll_flags=1; ON_QUIT(); break;\
*/

#endif


#endif


