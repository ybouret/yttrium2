
//! \file

#ifndef Y_JSON_Compiler_Included
#define Y_JSON_Compiler_Included 1

#include "y/json/value.hpp"
#include "y/jive/source.hpp"

namespace Yttrium
{

    namespace JSON
    {

        class Compiler
        {
        public:
            explicit Compiler();
            virtual ~Compiler() noexcept;

            void operator()( Value &value, Jive::Source & );

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Compiler);
            Code * const code;
        public:
            bool &verbose;
        };

    }

}

#endif

