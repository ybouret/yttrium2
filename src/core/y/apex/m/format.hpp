

//! \file

#ifndef Y_Apex_Format_Included
#define Y_Apex_Format_Included 1

#include "y/apex/m/size-for.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Apex
    {

     
        template <typename U>
        struct UFormat
        {
            static inline
            U * Make(natural_t &data, const size_t size) noexcept
            {
                assert(size<=sizeof(natural_t)/sizeof(U));
                natural_t        v = data;
                U        * const u = (U *) &data;
                for(size_t i=0;i<size;++i)
                {
                    u[i] = U(v);
                    v >>= 8*sizeof(U);
                }
                return u;
            }

        };

        template <typename T> inline
        const T * UFormatAs(natural_t &data, size_t &size)
        {
            size          = SizeFor<T>::From( Calculus::BitsFor::Count(data) );
            return UFormat<T>::Make(data,size);
        }
    }

}

#endif

