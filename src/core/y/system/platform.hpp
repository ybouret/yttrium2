
//! \file

#ifndef Y_System_Platform_Included
#define Y_System_Platform_Included 1

#undef Y_Platform


#if defined(__linux__)
#define Y_BSD       1
#define Y_Platform "Linux"
#endif

#if defined(__APPLE__)
#define Y_BSD       1
#define Y_Platform "Apple"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define Y_WIN       1
#define Y_Platform "Windows"
#endif

#if defined(__FreeBSD__)
#define Y_BSD 1
#define Y_Platform "FreeBSD"
#endif

#if defined(__sun__)
#define Y_BSD 1
#define Y_Platform "Sun"
#endif

#if !defined(Y_Platform)
#error "Unknown Platform"
#endif



#endif

