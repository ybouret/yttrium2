

//! \file

#ifndef Y_Jive_RegExp_Compiler_Included
#define Y_Jive_RegExp_Compiler_Included 1

#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class RegExp:: Compiler
        {
        public:
            static const char * const CallSign;

            Compiler(const String &, const Dictionary * const) noexcept;
            ~Compiler() noexcept;

            Pattern *subExpr();


            const char *             curr;
            const char * const       last;
            unsigned                 deep;
            const char * const       expr;
            const Dictionary * const dict;

        private:
            Y_Disable_Copy_And_Assign(Compiler);
        };

    }

}

#endif
