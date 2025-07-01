

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
            uint64_t * Make(natural_t &data, const size_t) noexcept
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
                natural_t  v = data;
                U        * u = (U *) &data;
                while(size-- > 0)
                {
                    *(u++) =   U(v);
                    v      >>= 8*sizeof(U);
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
            size          = SizeFor<T>::From( Calculus::BitsFor::Count(data) );
            return UFormat<T>::Make(data,size);
        }
    }

}

#endif

