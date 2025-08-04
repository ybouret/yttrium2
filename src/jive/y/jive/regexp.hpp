
//! \file

#ifndef Y_Jive_RegExp_Included
#define Y_Jive_RegExp_Included 1

#include "y/jive/pattern/dictionary.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //! Regular Expression API
        struct RegExp
        {
            class Compiler;
            static Pattern * Compile(const String &,     const Dictionary * const =0); //!< \return compiler expression
            static Pattern * Compile(const char * const, const Dictionary * const =0); //!< \return compiled expression
        };

    }

}

#endif

