//! \file

#ifndef Y_Type_Args_Included
#define Y_Type_Args_Included 1

#include "y/type/traits.hpp"

//______________________________________________________________________________
//
//
//! expose internal types for template type
//
//______________________________________________________________________________
#define Y_Args_Expose(T,TYPE)                              \
typedef T                                   TYPE;          \
typedef typename TypeTraits<T>::MutableType Mutable##TYPE; \
typedef const Mutable##TYPE                 Const##TYPE

//______________________________________________________________________________
//
//
//! expose internal types for specialized type
//
//______________________________________________________________________________
#define Y_Args_Expose_Spec(T,TYPE)                \
typedef T                          TYPE;          \
typedef TypeTraits<T>::MutableType Mutable##TYPE; \
typedef const Mutable##TYPE        Const##TYPE

//______________________________________________________________________________
//
//
//! declare internal types and parameter type
//
//______________________________________________________________________________
#define Y_Args_Declare(T,TYPE) \
Y_Args_Expose(T,TYPE); \
typedef typename TypeTraits<T>::ParamType Param##TYPE


//______________________________________________________________________________
//
//
//! declare internal types and parameter type for specialized type
//
//______________________________________________________________________________
#define Y_Args_Declare_Spec(T,TYPE)          \
Y_Args_Expose_Spec(T,TYPE);                  \
typedef TypeTraits<T>::ParamType Param##TYPE

#endif

