

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
            static const char LPAREN    = '(';  //!< alias
            static const char RPAREN    = ')';  //!< alias
            static const char ALT       = '|';  //!< alias
            static const char LBRACK    = '[';  //!< alias
            static const char RBRACK    = ']';  //!< alias
            static const char LBRACE    = '{';  //!< alias
            static const char RBRACE    = '}';  //!< alias
            static const char AMPERSAND = '&';  //!< alias
            static const char BACKSLASH = '\\'; //!< alias
            static const char CARET     = '^';  //!< alias

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
            Pattern *subExpr(); //!< \return new sub-expr from current position


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

            Pattern *subBank(); //!< \return new sub-bank from current position
            Pattern *goPosix(); //!< \return [:posix:]
            Pattern *escExpr(); //!< \return escape sequence in expr
            Pattern *escBank(); //!< \return escape sequence in bank
            Pattern *escHexa(); //!< \return escaped hexadecimal
            Pattern *nextByte(); //!< \return next byte in bank after '-'
            void     simpleJoker(Logic &, const char); //!< + | - | ?
            //void     bracesJoker();
        };

    }

}

#endif
