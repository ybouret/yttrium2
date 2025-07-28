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
            lastVec(0),
            vlist(),
            cache(sharedCache),
            next(0),
            prev(0)
            {
            }

            Family * Family:: replicate(const Family &F)
            {
                assert(0==vlist.size);
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
                return this;
            }

            Family:: Family(const Family &F) :
            Object(),
            Metrics(F),
            IFamily(),
            Recyclable(),
            quality(F.quality),
            lastVec(0),
            vlist(),
            cache(F.cache),
            next(0),
            prev(0)
            {
                (void) replicate(F);
            }



            Family::ConstInterface & Family::locus() const noexcept
            {
                return vlist;
            }


            void Family:: clear() noexcept
            {
                while(vlist.size) cache->store(vlist.popTail());
                Coerce(quality) = qualify(0);
                Coerce(lastVec) = 0;
            }


            void Family:: free() noexcept
            {
                clear();
            }

            Family:: ~Family() noexcept
            {
                clear();
            }



            Vector * Family:: orthogonalPart(Vector * const a)
            {
                assert(0!=a);
                const Vector *b = vlist.head;
                if(!b)
                {
                    if(a->ncof>0)
                        return a;
                    else
                    {
                        cache->store(a);
                        return 0;
                    }
                }
                else
                {
                    try
                    {
                        for(;b;b=b->next)
                        {
                            if( a->keepOrtho(*b) )
                            {
                                assert(a->ncof>0);
                                continue;
                            }
                            cache->store(a);
                            return 0;
                        }
                        assert(a->ncof>0);
                        return a;
                    }
                    catch(...)
                    {
                        cache->store(a); throw;
                    }
                }
            }

            bool Family:: verify(const Vector &v) const
            {
                if(v.ncof<=0) return false;
                assert(v.nrm2.bits()>0);
                for(const Vector *b=vlist.head;b;b=b->next)
                {
                    if( __Zero__ != b->dot(v) ) return false;
                }
                return true;
            }


            void Family:: progeny(Vector * const v) noexcept
            {
                assert(v);
                assert(verify(*v));
                Coerce(lastVec) = vlist.pushTail(v);
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


            Family * Family:: createNewFamilyWith(Vector * const ortho, Cache &fc)
            {
                assert(0!=ortho);
                //assert( verify(ortho) );
                try {
                    Family * F = fc.query(*this);
                    F->progeny(ortho);
                    return F;
                }
                catch(...)
                {
                    cache->store(ortho); throw;
                }

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

            Family * Family:: Cache:: query(const Family &F)
            {
                Family * const R = (fCache.size > 0 ? fCache.popHead() : new Family(vCache));
                try {
                    return R->replicate(F);
                }
                catch(...)
                {
                    store(R);
                    throw;
                }
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

