#include "y/apex/api/ortho/family.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {
            Family:: Family(const VCache &sharedCache) noexcept :
            CountedObject(),
            Metrics( *sharedCache ),
            IFamily(),
            Recyclable(),
            quality( qualify(0) ),
            ortho(0),
            vlist(),
            cache(sharedCache)
            {
            }

            Family:: Family(const Family &F) :
            CountedObject(),
            Metrics(F),
            IFamily(),
            Recyclable(),
            quality(F.quality),
            ortho(0),
            vlist(),
            cache(F.cache)
            {
                try {
                    for(const Vector *v = F.vlist.head;v;v=v->next)
                    {
                        if(cache->count()>0)
                        {
                            *vlist.pushTail( cache->query() ) = *v;
                        }
                        else
                        {
                            vlist.pushTail( new Vector(*v) );
                        }
                    }
                }
                catch(...)
                {
                    clear(); throw;
                }
            }



            Family::ConstInterface & Family::locus() const noexcept
            {
                return vlist;
            }

            void Family:: prune() noexcept
            {
                if(ortho) { cache->store(ortho); ortho = 0; }
            }

            void Family:: clear() noexcept
            {
                prune();
                while(vlist.size) cache->store(vlist.popTail());
                Coerce(quality) = qualify(0);
            }


            void Family:: free() noexcept
            {
                clear();
            }

            Family:: ~Family() noexcept
            {
                clear();
            }

            Vector & Family:: fetch()
            {
                if(!ortho) ortho = cache->query();
                assert(ortho);
                assert(ortho->dimensions==dimensions);
                return *ortho;
            }

            bool Family:: isBasis() noexcept
            {
                if(Basis==quality)
                {
                    prune();
                    return true;
                }
                else
                    return false;
            }


            bool Family:: isOrtho(Vector &a)
            {
                assert( ortho ); assert( &a == ortho );
                for(const Vector *b=vlist.head;b;b=b->next)
                {
                    if( a.keepOrtho(*b) ) continue;
                    prune();
                    return false;
                }
                return true;
            }


            void Family:: grow() noexcept
            {
                assert(0!=ortho);
                assert(ortho->ncof>0);
                assert(ortho->nrm2.bits()>0);
                vlist.pushTail(ortho); ortho = 0;
                vlist.sort(Vector::Compare);
                Coerce(quality) = qualify(vlist.size);
            }



        }

    }

}

