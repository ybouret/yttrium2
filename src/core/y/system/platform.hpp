
//! \file

#ifndef Y_System_Platform_Included
#define Y_System_Platform_Included 1

#undef Y_Platform


#if defined(__linux__)
#define Y_BSD       1
#define Y_Platform "Linux"
#define Y_Linux     1
#endif

#if defined(__APPLE__)
#define Y_BSD       1
#define Y_Platform "Apple"
#define Y_Darwin    1
#endif

#if defined(_WIN32) || defined(_WIN64)
#define Y_WIN       1
#define Y_Platform "Windows"
#endif

#if defined(__FreeBSD__)
#define Y_BSD       1
#define Y_Platform "FreeBSD"
#define Y_FreeBSD   1
#endif

#if defined(__NetBSD__)
#define Y_BSD       1
#define Y_Platform "NetBSD"
#define Y_NetBSD    1
#endif

#if defined(__sun__)
#define Y_BSD       1
#define Y_Platform "SunOS"
#define Y_SunOS
#endif

#if !defined(Y_Platform)
#error "Unknown Platform"
#endif



#endif

