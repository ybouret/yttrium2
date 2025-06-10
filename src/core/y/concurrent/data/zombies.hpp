
//! \file

#ifndef Y_Concurrent_Zombies_Included
#define Y_Concurrent_Zombies_Included 1

#include "y/core/linked/pool.hpp"
#include "y/type/ingress.hpp"
#include "y/memory/page.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        template <typename NODE>
        class Zombies : public Ingress< const Core::PoolOf<Memory::Page> >
        {
        public:
            typedef Memory::Page        Zombi;
            typedef Core::PoolOf<Zombi> ZombiPool;
            typedef Ingress<ZombiPool>  ZombiPoolAPI;

        private:
            Y_Disable_Copy_And_Assign(Zombies);
            ZombiPool my;
            typename ZombiPoolAPI::ConstInterface & locus() const noexcept { return my; }

        };

    }

}

#endif

