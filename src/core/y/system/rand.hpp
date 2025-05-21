
//! \file

#ifndef Y_System_Rand_Included
#define Y_System_Rand_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {

        class Rand
        {
        public:
            explicit Rand() noexcept;
            virtual ~Rand() noexcept;

            template <typename T>
            T to() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Rand);
        };

    }
}

#endif

