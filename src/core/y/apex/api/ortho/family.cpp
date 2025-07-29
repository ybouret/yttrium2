#include "y/apex/api/ortho/family.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {
            Family:: Family(Vector::Pool &vp) noexcept :
            Object(),
            Metrics(vp),
            IFamily(),
            Recyclable(),
            quality( qualify(0) ),
            lastVec(0),
            vlist(),
            vpool(vp),
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
                        if(vpool.count()>0)
                        {
                            *vlist.pushTail( vpool.query() ) = *v;
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
            vpool(F.vpool),
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
                while(vlist.size) vpool.store(vlist.popTail());
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
                        vpool.store(a);
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
                            vpool.store(a);
                            return 0;
                        }
                        assert(a->ncof>0);
                        return a;
                    }
                    catch(...)
                    {
                        vpool.store(a); throw;
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
                os << "\t\t# <Family #" << F->size << "/" << F.dimensions << " is " << F.humanReadableQuality() << ">" << std::endl;
                size_t i=1;
                for(const Vector *v=F->head;v;v=v->next,++i)
                {
                    os << "\t\t\te" << i << " = " << *v << std::endl;
                }
                return os << "\t\t# </Family>";
            }


            Family * Family:: createNewFamilyWith(Vector * const ortho, Pool &fc)
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
                    vpool.store(ortho); throw;
                }

            }

            size_t Family:: size() const noexcept { return vlist.size; }



            bool operator==(const Family & lhs, const Family & rhs) noexcept
            {
                if(lhs->size!=rhs->size) return false;

                for(const Vector *l=lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
                {
                    switch(Vector::Compare(l,r))
                    {
                        case Negative: return false;
                        case Positive: return false;
                        case __Zero__: continue;
                    }
                }
                return true;
            }

#if 0
            SignType Family:: Compare(const Family * const lhs, const Family * const rhs) noexcept
            {
                assert(lhs);
                assert(rhs);
                assert(lhs->vlist.size==rhs->vlist.size);

                for(const Vector *l = lhs->vlist.head, *r =rhs->vlist.head; l; l=l->next, r=r->next)
                {
                    assert(l);
                    assert(r);
                    switch( Vector::Compare(l,r) )
                    {
                        case Negative: return Negative;
                        case Positive: return Positive;
                        case __Zero__: continue;
                    }
                }
                
                return __Zero__;
            }
#endif
            
            //------------------------------------------------------------------

            Family:: Pool:: Pool(Vector::Pool &vp) noexcept :
            Metrics(vp),
            Caching(),
            vpool(vp),
            flist()
            {
            }

            Family:: Pool:: ~Pool() noexcept
            {
            }

            void Family:: Pool:: store(Family *const F) noexcept
            {
                assert(0!=F);
                flist.pushHead(F)->clear();
            }

            Family * Family:: Pool:: query()
            {
                return (flist.size > 0 ? flist.popHead() : new Family(vpool));
            }

            Family * Family:: Pool:: query(const Family &F)
            {
                Family * const R = query();
                try {
                    return R->replicate(F);
                }
                catch(...)
                {
                    store(R);
                    throw;
                }
            }


            size_t Family:: Pool:: count() const noexcept
            {
                return flist.size;
            }

            void Family:: Pool:: cache(const size_t n)
            {
                for(size_t i=n;i>0;--i) {
                    flist.pushTail( new Family(vpool) );
                }
            }

            void Family:: Pool:: gc(const uint8_t amount) noexcept
            {
                flist.sortByIncreasingAddress();
                const size_t newSize = NewSize(amount,flist.size);
                while(flist.size>newSize) delete flist.popTail();
            }


            //------------------------------------------------------------------
            

        }

    }

}

