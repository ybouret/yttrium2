#include "y/apex/api/ortho/family.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {
            Family:: Family(const VCache &sharedCache) noexcept :
            Object(),
            Metrics( *sharedCache ),
            IFamily(),
            Recyclable(),
            quality( qualify(0) ),
            ortho(0),
            vlist(),
            cache(sharedCache),
            next(0),
            prev(0)
            {
            }

            Family:: Family(const Family &F) :
            Object(),
            Metrics(F),
            IFamily(),
            Recyclable(),
            quality(F.quality),
            ortho(0),
            vlist(),
            cache(F.cache),
            next(0),
            prev(0)
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
                const Vector *b = vlist.head;
                if(!b)
                {
                    return a.ncof>0;
                }
                else
                {
                    for(;b;b=b->next)
                    {
                        if( a.keepOrtho(*b) )
                        {
                            assert(a.ncof>0);
                            continue;
                        }
                        prune();
                        return false;
                    }
                    assert(a.ncof>0);
                    return true;
                }


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


            const char * Family:: humanReadableQuality() const noexcept
            {
                return HumanReadableQuality(quality);
            }

            std::ostream & operator<<(std::ostream &os, const Family &F)
            {
                os << "# <Family #" << F->size << "/" << F.dimensions << " is " << F.humanReadableQuality() << ">" << std::endl;
                size_t i=1;
                for(const Vector *v=F->head;v;v=v->next,++i)
                {
                    os << "\te" << i << " = " << *v << std::endl;
                }
                return os << "# </Family>";
            }

            const Vector & Family:: last() const noexcept
            {
                assert(0!=ortho);
                return *ortho;
            }


            bool Family:: includes(const Family &F)
            {
                if(Basis == quality) return true;
                for(const Vector *v = F.vlist.head;v;v=v->next)
                {
                    if(!contains(*v)) return false;
                }
                return true;
            }


            //------------------------------------------------------------------

            Family:: Cache:: Cache(const VCache &vc) noexcept :
            CountedObject(),
            Metrics(*vc),
            Caching(),
            vCache(vc),
            fCache()
            {
            }

            Family:: Cache:: ~Cache() noexcept
            {
            }

            void Family:: Cache:: store(Family *const F) noexcept
            {
                assert(0!=F);
                fCache.pushHead(F)->clear();
            }

            Family * Family:: Cache:: query()
            {
                return fCache.size > 0 ? fCache.popHead() : new Family(vCache);
            }


            size_t Family:: Cache:: count() const noexcept
            {
                return fCache.size;
            }

            void Family:: Cache:: cache(const size_t n)
            {
                for(size_t i=n;i>0;--i) {
                    fCache.pushTail( new Family(vCache) );
                }
            }

            void Family:: Cache:: gc(const uint8_t amount) noexcept
            {
                fCache.sortByIncreasingAddress();
                const size_t newSize = NewSize(amount,fCache.size);
                while(fCache.size>newSize) delete fCache.popTail();
            }

        }

    }

}

