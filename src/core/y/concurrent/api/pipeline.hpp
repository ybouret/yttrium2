
//! \file

#ifndef Y_Concurrent_Pipeline_Included
#define Y_Concurrent_Pipeline_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/pipeline/task.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Pipeline to carry out independent tasks
        //
        //
        //______________________________________________________________________
        class Pipeline : public Parallel
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            explicit Pipeline(const size_t, const char * const);

        public:
            //! cleanup
            virtual ~Pipeline() noexcept;

        protected:
            Task::ID counter; //!< global task counter

        private:
            Y_Disable_Copy_And_Assign(Pipeline); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

