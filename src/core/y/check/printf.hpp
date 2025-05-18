
//! \file


#ifndef Y_Check_Printf_Included
#define Y_Check_Printf_Included 1

#include "y/system/compiler.hpp"

#include <cstdio>

#if defined(Y_CLANG) || defined(Y_GNU)
#define Y_Printf_Check(FORMAT_POS,ELLIPSIS_POS) \
__attribute__((__format__(__printf__, FORMAT_POS, ELLIPSIS_POS)));
#else
#define Y_Printf_Check(FORMAT_POS,ELLIPSIS_POS)
#endif

#endif

