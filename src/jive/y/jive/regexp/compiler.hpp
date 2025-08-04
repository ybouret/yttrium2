

//! \file

#ifndef Y_Jive_RegExp_Compiler_Included
#define Y_Jive_RegExp_Compiler_Included 1

#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Regular Expression Compiler
        //
        //
        //______________________________________________________________________
        class RegExp:: Compiler
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Jive::RegExp"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Compiler(const String &, const Dictionary * const) noexcept;
            ~Compiler() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Pattern *subExpr(); //!< new sub-expression from current position

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const char *             curr; //!< current position
            const char * const       last; //!< first invalid position
            unsigned                 deep; //!< current nesting level
            const char * const       expr; //!< original expression
            const Dictionary * const dict; //!< optional dictionary

        private:
            Y_Disable_Copy_And_Assign(Compiler); //!< dicarding
        };

    }

}

#endif
