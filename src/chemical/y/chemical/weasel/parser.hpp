//! \file


#ifndef Y_Chemical_Weasel_Parser_Included
#define Y_Chemical_Weasel_Parser_Included 1

#include "y/chemical/weasel.hpp"
#include "y/jive/parser.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        class Weasel:: Parser : public Jive::Parser
        {
        public:
            explicit Parser();
            virtual ~Parser() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Parser);
        };

    }

}

#endif
