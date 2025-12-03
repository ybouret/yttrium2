
//! \file

#ifndef Y_Libc_Types_Included
#define Y_Libc_Types_Included 1

#include "y/type/shallow.hpp"

namespace Yttrium
{

    Y_Shallow_Decl(StdIn);  //!< alias
    Y_Shallow_Decl(StdOut); //!< alias
    Y_Shallow_Decl(StdErr); //!< alias

#define Y_STDIN  ":STDIN:"  //!< special name
#define Y_STDERR ":STDERR:" //!< special name
#define Y_STDOUT ":STDOUT:" //!< special name

}

#endif // !Y_Libc_Types_Included

