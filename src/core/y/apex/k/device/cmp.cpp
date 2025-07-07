
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        namespace
        {
            template <typename T>
            struct ParcelCmp
            {

                static inline
                SignType Get(const Parcel<T> &lhs, const Parcel<T> &rhs) noexcept
                {
                    assert( lhs.sanity() );
                    assert( rhs.sanity() );

                    size_t n = lhs.size;
                    switch( Sign::Of(n,rhs.size) )
                    {
                        case Negative: return Negative;
                        case Positive: return Positive;
                        case __Zero__: break;
                    }

                    {
                        const T * l = lhs.data+n;
                        const T * r = rhs.data+n;
                        while(n-- > 0)
                        {
                            switch( Sign::Of( *(--l), *(--r) ) )
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
                SignType Get( const Device &lhs, const Device &rhs ) noexcept
                {
                    return Get( lhs.make<T>(), rhs.make<T>() );
                }

                static inline
                SignType Get(const Device &lhs, natural_t rhs) noexcept
                {
                    const Parcel<T> n(rhs);
                    return Get(lhs.make<T>(), n);
                }

                static inline
                SignType Get(natural_t lhs, const Device &rhs ) noexcept
                {
                    const Parcel<T> n(lhs);
                    return Get(n,rhs.make<T>());
                }

            };
        }

        SignType Device:: Compare(const Device & lhs,
                                  const Device & rhs,
                                  const PlanType cmp) noexcept
        {
            typedef SignType (*Cmp)(const Device &, const Device &);
            static Cmp const Table[Metrics::Views] =
            {
                ParcelCmp<uint8_t>::Get,
                ParcelCmp<uint16_t>::Get,
                ParcelCmp<uint32_t>::Get,
                ParcelCmp<uint64_t>::Get
            };
            return Table[cmp](lhs,rhs);
        }

        SignType Device:: Compare(const Device &  lhs,
                                  const natural_t rhs,
                                  const PlanType  cmp) noexcept
        {
            typedef SignType (*Cmp)(const Device &, const natural_t);
            static Cmp const Table[Metrics::Views] =
            {
                ParcelCmp<uint8_t>::Get,
                ParcelCmp<uint16_t>::Get,
                ParcelCmp<uint32_t>::Get,
                ParcelCmp<uint64_t>::Get
            };
            return Table[cmp](lhs,rhs);
        }

        SignType Device:: Compare(const natural_t lhs,
                                  const Device &  rhs,
                                  const PlanType  cmp) noexcept
        {
            typedef SignType (*Cmp)(const natural_t, const Device &);
            static Cmp const Table[Metrics::Views] =
            {
                ParcelCmp<uint8_t>::Get,
                ParcelCmp<uint16_t>::Get,
                ParcelCmp<uint32_t>::Get,
                ParcelCmp<uint64_t>::Get
            };
            return Table[cmp](lhs,rhs);
        }

    }
}


