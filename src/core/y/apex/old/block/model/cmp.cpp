#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/check/usual.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {

        template <typename T>
        struct ModelCmp
        {
            static inline SignType Of(const T * const lhs,
                                      const size_t    nl,
                                      const T * const rhs,
                                      const size_t    nr) noexcept
            {
                assert(Good(lhs,nl));
                assert(Good(rhs,nr));
                //Hexadecimal::Display(std::cerr << "cmp: ",lhs,nl);
                //Hexadecimal::Display(std::cerr,rhs,nr) << std::endl;

                switch( Sign::Of(nl,nr) )
                {
                    case Negative:
                        assert(nl<nr);
                        assert(0!=rhs);
                        assert(0!=rhs[nr-1]);
                        return Negative;

                    case Positive:
                        assert(nl>nr);
                        assert(0!=lhs);
                        assert(0!=lhs[nl-1]);
                        return Positive;

                    case __Zero__:
                        break;
                }

                {
                    assert(nl==nr);
                    size_t   n = nl;
                    const T *l = lhs+n;
                    const T *r = rhs+n;
                    while(n-- > 0)
                    {
                        switch( Sign::Of(*(--l),*(--r)))
                        {
                            case Negative: return Negative;
                            case Positive: return Positive;
                            case __Zero__: continue;
                        }
                    }
                }
                return __Zero__;
            }

            static inline
            SignType Of_(const Block<T> &lhs, const Block<T> &rhs) noexcept
            {
                return Of(lhs.data,lhs.size,rhs.data,rhs.size);
            }

            static inline
            SignType Of(const Model &lhs, const Model &rhs) noexcept
            {
                return Of_( lhs.get<T>(), rhs.get<T>() );
            }

            static inline
            SignType Of(const Model &lhs, natural_t n)
            {
                const Block<T> & L   = lhs.get<T>();
                size_t           nr  = 0;
                const T * const  rhs = UFormatAs<T>(n,nr);
                return Of(L.data,L.size,rhs,nr);
            }

        };




        SignType Model:: Compare(const Model &lhs, const Model &rhs)
        {
            typedef SignType (*Cmp)(const Model &, const Model &);
            static  Cmp  const CmpTable[Metrics::Views] =
            {
                ModelCmp<uint8_t> ::Of,
                ModelCmp<uint16_t>::Of,
                ModelCmp<uint32_t>::Of,
                ModelCmp<uint64_t>::Of,
            };

            switch( Sign::Of(lhs.view,rhs.view) )
            {
                case Negative: {
                    // use rhs.view
                    const ViewType       v = rhs.view;
                    const AutoPtr<Model> l = new Model(lhs,v);
                    return CmpTable[v](*l,rhs);
                }
                case Positive: {
                    // use lhs.view
                    const ViewType       v = lhs.view;
                    const AutoPtr<Model> r = new Model(rhs,v);
                    return CmpTable[v](lhs,*r);
                }
                case __Zero__: // same views
                    break;
            }
            return CmpTable[lhs.view](lhs,rhs);
        }

        SignType Model:: Compare(const Model &m, const natural_t n) noexcept
        {
            typedef SignType (*Cmp)(const Model &, natural_t);
            static  Cmp  const CmpTable[Metrics::Views] =
            {
                ModelCmp<uint8_t> ::Of,
                ModelCmp<uint16_t>::Of,
                ModelCmp<uint32_t>::Of,
                ModelCmp<uint64_t>::Of,
            };
            return CmpTable[m.view](m,n);
        }

        

    }

}


