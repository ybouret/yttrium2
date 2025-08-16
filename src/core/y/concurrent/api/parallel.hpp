
//! \file

#ifndef Y_Concurrent_Parallel_Included
#define Y_Concurrent_Parallel_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Parallel  : public Identifiable
        {
        protected:
            explicit Parallel(const size_t, const char * const);

        public:
            virtual ~Parallel() noexcept;

            const size_t size;

        private:
            Y_Disable_Copy_And_Assign(Parallel);
        };

    }


}

#endif

