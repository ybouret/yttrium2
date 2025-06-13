
//! \file

#ifndef Y_Libc_Types_Included
#define Y_Libc_Types_Included 1

#include "y/type/shallow.hpp"

namespace Yttrium
{

    Y_Shallow_Decl(StdIn);
    Y_Shallow_Decl(StdOut);
    Y_Shallow_Decl(StdErr);

#define Y_STDIN  ":STDIN:"
#define Y_STDERR ":STDERR:"
#define Y_STDOUT ":STDOUT:"

}

#endif

