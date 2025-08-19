
//! \file

#ifndef Y_Jive_Analyzer_Included
#define Y_Jive_Analyzer_Included 1


#include "y/jive/syntax/node.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Analyzer
        {
        public:
            explicit Analyzer(const bool verbose);
            virtual ~Analyzer() noexcept;

            void operator()(const XNode * const root);

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Analyzer);
            Code * const code;
            
        };
    }

}

#endif


