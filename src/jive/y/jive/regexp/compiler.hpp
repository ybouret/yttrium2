

//! \file

#ifndef Y_Jive_RegExp_Compiler_Included
#define Y_Jive_RegExp_Compiler_Included 1

#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Logic;
        
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
            static const char LPAREN    = '('; //!< alias
            static const char RPAREN    = ')'; //!< alias
            static const char ALT       = '|'; //!< alias
            static const char LBRACK    = '[';
            static const char RBRACK    = ']';
            static const char LBRACE    = '{';
            static const char RBRACE    = '}';
            static const char AMPERSAND = '&';
            static const char BACKSLASH = '\\';

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Compiler(const String &, const Dictionary * const) noexcept; //!< setup from persistent data
            ~Compiler() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Pattern *subExpr(); //!< \return new sub-expression from current position
            void     escExpr(Logic &);
            void     simpleJoker(Logic &, const char);
            //void     bracesJoker();

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
