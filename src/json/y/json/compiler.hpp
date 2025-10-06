
//! \file

#ifndef Y_JSON_Compiler_Included
#define Y_JSON_Compiler_Included 1

#include "y/json/value.hpp"
#include "y/jive/source.hpp"

namespace Yttrium
{

    namespace JSON
    {

        //______________________________________________________________________
        //
        //
        //
        //! Compiler
        //
        //
        //______________________________________________________________________
        class Compiler
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Compiler();          //!< setup
            virtual ~Compiler() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void operator()(Value &, Jive::Source &); //!< put in value content of source

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Compiler); //!< discarding
            Code * const code;                   //!< inner code
        public:
            bool &verbose;                       //!< verbosity
        };

    }

}

#endif // !Y_JSON_Compiler_Included

