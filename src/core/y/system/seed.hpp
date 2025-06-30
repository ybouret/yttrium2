//! \file

#ifndef Y_System_Rand_Included
#define Y_System_Rand_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace System
    {
        //! computing seeds from system
        struct Seed
        {
            //! fill memory with system random bytes
            static void Fill(void * const, const size_t);

            //! get by filling bytes \return random integral seed
            template <typename T> static inline
            T Get()
            {
                T res = 0;
                Fill(&res,sizeof(res));
                return res;
            }

        };
    }

}

#endif

