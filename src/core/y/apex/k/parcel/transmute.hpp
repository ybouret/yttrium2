
//! \file

#ifndef Y_Apex_Parcel_Transmute_Included
#define Y_Apex_Parcel_Transmute_Included 1

#include "y/apex/k/parcel.hpp"
#include "y/check/static.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{
    namespace Apex
    {
        struct Transmute
        {

            //! Expand Parcels with synchronized size
            template <typename SMALL, typename LARGE> static inline
            void Expand(Parcel<SMALL>       &small,
                        const Parcel<LARGE> &large) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadType);
                static const unsigned SmallBits = sizeof(SMALL)*8;
                SMALL *       tgt = small.data;
                const LARGE * src = large.data;
                for(size_t i=large.size;i>0;--i)
                {
                    LARGE value = *(src++);
                    for(size_t j=sizeof(LARGE)/sizeof(SMALL);j>0;--j, value>>=SmallBits)
                        *(tgt++) = SMALL(value);
                }

            }

            //! Shrink Parcels with synchronized size
            template <typename LARGE, typename SMALL> static inline
            void Shrink(Parcel<LARGE>       &large,
                        const Parcel<SMALL> &small) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadType);
                static const unsigned SmallBits = sizeof(SMALL)*8;
                LARGE *       tgt = large.data;
                const SMALL * src = small.data;
                for(size_t i=large.size;i>0;--i)
                {
                    LARGE value = 0;
                    for(unsigned j=0;j<sizeof(LARGE)/sizeof(SMALL);++j)
                    {
                        LARGE tmp = *(src++);
                        tmp  <<= SmallBits*j;
                        value |=  tmp;
                    }
                    *(tgt)++ = value;
                }
            }

            template <typename SMALL, typename LARGE> static inline
            void To(Parcel<SMALL>       &      small,
                    const Parcel<LARGE> &      large,
                    const IntToType<Negative> &) noexcept
            {
                Expand(small,large);
            }

            template <typename T> static inline
            void To(Parcel<T>       & ,
                    const Parcel<T> & ,
                    const IntToType<__Zero__> &) noexcept
            {
            }

            template <typename LARGE, typename SMALL> static inline
            void To(Parcel<LARGE>       &      large,
                    const Parcel<SMALL> &      small,
                    const IntToType<Positive> &) noexcept
            {
                Shrink(large,small);
            }

            template <const unsigned lhs, const unsigned rhs>
            struct SignOf
            {
                static const SignType Value = (lhs<rhs) ? Negative : ( (rhs<lhs) ? Positive : __Zero__ );
            };


            template <typename TARGET, typename SOURCE> static inline
            void To(Parcel<TARGET>       & target,
                    const Parcel<SOURCE> & source) noexcept
            {
                static const IntToType< SignOf< sizeof(TARGET), sizeof(SOURCE) >::Value > choice = {};
                return To(target,source,choice);
            }


        };
    }

}


#endif

