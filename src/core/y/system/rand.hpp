
//! \file

#ifndef Y_System_Rand_Included
#define Y_System_Rand_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {

        //______________________________________________________________________
        //
        //
        //
        //! rand() wrapper
        //
        //
        //______________________________________________________________________
        class Rand
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //
            //__________________________________________________________________
            explicit Rand() noexcept;
            virtual ~Rand() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            //! convert to [float|double|long double]
            /** \return "]0:1[" */
            template <typename T> T to() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Rand); //!< discarding
        };

    }
}

#endif

