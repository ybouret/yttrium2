
//! \file

#ifndef Y_Concurrent_Pipeline_Included
#define Y_Concurrent_Pipeline_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/context.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Pipeline : public Parallel
        {
        protected:
            explicit Pipeline(const size_t, const char * const);

        public:
            virtual ~Pipeline() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Pipeline);
        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

