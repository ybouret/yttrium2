
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/apex/api/coven/tribe.hpp"


namespace Yttrium
{

    namespace Coven
    {

        class Tribes : public Tribe::List
        {
        public:
            explicit Tribes(IPool        &ip,
                            Tribe::Cache &tc,
                            const size_t  n) :
            Tribe::List(),
            idxPool(ip),
            trCache(tc)
            {
                for(size_t first=1;first<=n;++first)
                {
                    Tribe *tr = trCache.summon(ip,n,first);
                    pushTail(tr);
                    std::cerr << *tr << std::endl;
                }
            }

            virtual ~Tribes() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Tribes);
            IPool        idxPool;
            Tribe::Cache trCache;
        };

    }

}

#endif

