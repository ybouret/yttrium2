
//! \file

#ifndef Y_Concurrent_Crew_Included
#define Y_Concurrent_Crew_Included 1

#include "y/concurrent/api/loop.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Crew : public Loop
        {
        public:
            static const char * const CallSign;
            
            explicit Crew(const size_t);
            virtual ~Crew() noexcept;

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Crew);
            Code * const code;
        };
    }

}

#endif
