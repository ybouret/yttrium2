//! \file

#ifndef Y_System_Compiler_Included
#define Y_System_Compiler_Included 1

#undef Y_Known_Compiler

#if defined(__clang__)
#define Y_Known_Compiler 1
#define Y_Compiler "clang"
#define Y_CLANG
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define Y_Known_Compiler 1
#define Y_Compiler "gnu"
#define Y_GNU
#endif


#if !defined(Y_Known_Compiler)
#error "Unknown Compiler"
#endif

#endif

