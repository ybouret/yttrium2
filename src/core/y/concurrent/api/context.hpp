
//! \file

#ifndef Y_Concurrent_Context_Included
#define Y_Concurrent_Context_Included 1

#include "y/ability/lockable.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Context
        {
        public:
            explicit Context(Lockable &, const size_t sz, const size_t rk) noexcept;
            virtual ~Context() noexcept;
            Y_OSTREAM_PROTO(Context);
            Lockable &   sync; //!< for local thread access
            const size_t size; //!< total number of threads
            const size_t rank; //!< local rank
            const size_t indx; //!< local indx=rank+1



        private:
            Y_Disable_Copy_And_Assign(Context);

        };

    }

}

#endif

