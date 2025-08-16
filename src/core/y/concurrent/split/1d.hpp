
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/concurrent/split/segment.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {


            class In1D
            {
            public:
                In1D(const size_t count) noexcept;
                virtual ~In1D() noexcept;

                void boot(const size_t nproc) noexcept;
                bool next() noexcept;


                const size_t offset; //!< C++ [1..origin]
                const size_t length; //!< dedicated length
                
            private:
                size_t       divide;
                size_t       remain;
            public:
                const size_t origin;
            private:
                Y_Disable_Copy_And_Assign(In1D);
            };

        }

    }
}

#endif

