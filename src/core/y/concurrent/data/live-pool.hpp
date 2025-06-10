
//! \file

#ifndef Y_Concurrent_Live_Pool_Included
#define Y_Concurrent_Live_Pool_Included 1

#include "y/core/linked/list.hpp"
#include "y/type/ingress.hpp"
#include "y/concurrent/data/dead-pool.hpp"
#include "y/memory/page.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        template <typename NODE>
        class LivePool : public Ingress< const Core::ListOf<Memory::Page> >
        {
        public:
            

        private:

        };

    }

}

#endif

