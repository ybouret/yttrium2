//! \file

#ifndef Y_System_Compiler_Included
#define Y_System_Compiler_Included 1

#undef Y_Compiler


// detect clang

#if defined(__clang__)
#  define Y_Compiler "Clang"
#  define Y_CLANG 1
#endif

// detect Intel
#if defined(__INTEL_COMPILER)
#  define Y_Compiler "Intel"
#  define Y_ICC 1
#  define noexcept throw()
#endif

#if defined(_MSC_VER)
#  define Y_Compiler "Microsoft"
#  define Y_MSC 1
#  pragma warning ( disable : 4514 4820 4625 4626 5026 5027 4774 4710 4711 4571 5039 5045 4435)

// for virtual base class
#  pragma warning ( disable : 4589)
#endif

// detect GNU
#if !defined(Y_Compiler) && defined(__GNUC__)
#  define Y_Compiler "GNU"
#  define Y_GNU 1
#  if(__GNUC__<7)
#  define noexcept throw()
#  endif
#endif



#if !defined(Y_Compiler)
#  error "Unknown Compiler"
#endif

#if defined(__cplusplus)
#include <cstdint>
#include <cstddef>
#else
#include <stdint.h>
#include <stddef.h>
#endif

#if defined(_MSC_VER)
#define        Y_U64(X) X##ui64
#define        Y_I64(X) X##i64
#else
#    define    Y_U64(X) X##ULL //!< helper
#    define    Y_I64(X) X##LL  //!< helper
#endif

#if defined(__cplusplus)
namespace Yttrium
{
    typedef ptrdiff_t unit_t;
}
#endif

#endif

