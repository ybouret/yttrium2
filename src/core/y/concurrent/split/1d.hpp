
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //__________________________________________________________________
            //
            //
            //
            //! Stable burden division
            //
            //
            //__________________________________________________________________
            class In1D
            {
            public:
                In1D(const size_t) noexcept;
                virtual ~In1D() noexcept;

                void boot(const size_t numProcessors,
                          const size_t initialOffset) noexcept;
                bool next() noexcept;


                const size_t offset; //!< cumulative offset
                const size_t length; //!< dedicated  length from offset

            private:
                size_t       divide;
                size_t       remain;
            public:
                const size_t burden;
            private:
                Y_Disable_Copy_And_Assign(In1D);
            };

        }

    }
}

#endif

