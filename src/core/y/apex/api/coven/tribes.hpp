
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/apex/api/coven/tribe.hpp"
#if Y_Coven_Stamp
#include "y/exception.hpp"
#endif

namespace Yttrium
{

    namespace Coven
    {

        class Tribes : public Tribe::List
        {
        public:
            explicit Tribes(const IPool        &ip,
                            const Tribe::Cache &tc,
                            const size_t        n) :
            Tribe::List(),
            idxPool(ip),
            trCache(tc)
            {
                for(size_t first=1;first<=n;++first)
                {
                    Tribe *tr = trCache.summon(ip,n,first);
                    pushTail(tr);
                    std::cerr << *tr << std::endl;
#if Y_Coven_Stamp
                    const IList &stamp = tr->stamp;
                    for(const Tribe *prev=tr->prev;prev;prev=prev->prev)
                    {
                        if(prev->stamp==stamp) throw Exception("Multiple Original Stamps");
                    }
#endif
                }
            }

            explicit Tribes(const IPool        &ip,
                            const Tribe::Cache &tc) noexcept;

            virtual ~Tribes() noexcept;

            inline size_t generate()
            {

                {
                    Tribes heirs(idxPool,trCache);
                    for(const Tribe *tr=head;tr;tr=tr->next)
                    {
                        tr->generate(heirs,trCache);
                    }
#if Y_Coven_Stamp
                    for(const Tribe *heir=heirs.head;heir;heir=heir->next)
                    {
                        for(const Tribe *prev=heir->prev;prev;prev=prev->prev)
                        {
                            if(prev->stamp==heir->stamp) throw Exception("Multiple Inherited Stamps");
                        }
                    }
#endif
                    swapListFor(heirs);
                }
                return size;
            }
            

        private:
            Y_Disable_Copy_And_Assign(Tribes);
            IPool        idxPool;
            Tribe::Cache trCache;
        };

    }

}

#endif

