
//! \file

#ifndef Y_JSON_Compiler_Included
#define Y_JSON_Compiler_Included 1

#include "y/json/value.hpp"

#include "y/jive/parser.hpp"
#include "y/jive/analyzer.hpp"

namespace Yttrium
{

    namespace JSON
    {

        class Compiler : public Jive::Parser
        {
        public:
            explicit Compiler();
            virtual ~Compiler() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Compiler);
        };

    }

}

#endif

