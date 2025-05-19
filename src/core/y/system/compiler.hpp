//! \file

#ifndef Y_System_Compiler_Included
#define Y_System_Compiler_Included 1

#undef Y_Compiler

// detect clang

#if defined(__clang__)
#define Y_Compiler "Clang"
#define Y_CLANG 1
#endif

// detect Intel
#if defined(__INTEL_COMPILER)
#define Y_Compiler "Intel"
#define Y_ICC 1
#define noexcept throw()
#endif

#if defined(_MSC_VER)
#define Y_Compiler "Microsoft"
#define Y_MSC 1
#endif

// detect GNU
#if !defined(Y_Compiler) && defined(__GNUC__)
#define Y_Compiler "GNU"
#define Y_GNU 1
#endif



#if !defined(Y_Compiler)
#error "Unknown Compiler"
#endif

#endif

