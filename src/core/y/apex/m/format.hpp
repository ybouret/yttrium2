

//! \file

#ifndef Y_Apex_Format_Included
#define Y_Apex_Format_Included 1

#include "y/apex/m/size-for.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Apex
    {

        template <typename U> struct UFormat;

        template <>
        struct UFormat<natural_t>
        {
            static inline
            const uint64_t * Make(natural_t &data, const size_t) noexcept
            {
                return &data;
            };
        };

        //! convert natural_t into big-endian, in place words
        template <typename U>
        struct UFormat
        {
            //! conversion of natural_t into T[]
            /**
             \param data original value, final workspace
             \param size pre-computed number of words
             \return workspace ready for Model ops
             */
            static inline
            U * Make(natural_t &data, size_t size) noexcept
            {
                assert(size<=sizeof(natural_t)/sizeof(U));
                static const unsigned shr = 8 * sizeof(U);
                natural_t  v = data;
                U * const  u = (U *) &data;
                for(size_t i=0;i<size;++i)
                {
                    u[i] = U(v);
                    v  >>= shr;
                }
                return u;
            }

        };

        //! transform natural_t into T[]
        /**
         \param data original value, final workspace
         \param size computed according to data bits
         \return workspace ready for Model ops
         */
        template <typename T> inline
        const T * UFormatAs(natural_t &data, size_t &size)
        {
            size = SizeFor<T>::From( Calculus::BitsFor::Count(data) );
            return UFormat<T>::Make(data,size);
        }
    }

}

#endif

