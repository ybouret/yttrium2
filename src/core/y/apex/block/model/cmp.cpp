#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/check/usual.hpp"


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
            SignType Of(const Block<T> &lhs, const Block<T> &rhs) noexcept
            {
                return Of(lhs.data,lhs.size,rhs.data,rhs.size);
            }

            static inline
            SignType Of(Model &lhs, Model &rhs) noexcept
            {
                return Of(lhs.make<T>(),rhs.make<T>());
            }
        };




        SignType Model:: Compare(Model &lhs, Model &rhs) noexcept
        {
            typedef SignType (*Cmp)(Model &, Model &);
            static  Cmp  const CmpTable[Metrics::Views] =
            {
                ModelCmp<uint8_t> ::Of,
                ModelCmp<uint16_t>::Of,
                ModelCmp<uint32_t>::Of,
                ModelCmp<uint64_t>::Of,
            };

            switch( Sign::Of(lhs.view,rhs.view) )
            {
                case Negative: return CmpTable[rhs.view](lhs,rhs);
                case Positive: return CmpTable[lhs.view](lhs,rhs);
                case __Zero__:
                    break;
            }
            return CmpTable[lhs.view](lhs,rhs);
        }

    }

}


