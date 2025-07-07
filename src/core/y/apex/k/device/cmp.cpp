
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

                    const size_t nl = lhs.size;
                    switch( Sign::Of(nl,rhs.size) )
                    {
                        case Negative: return Negative;
                        case Positive: return Positive;
                        case __Zero__: break;
                    }
                    


                }

            };
        }

    }
}


