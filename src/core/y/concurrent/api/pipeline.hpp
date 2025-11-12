
//! \file

#ifndef Y_Concurrent_Pipeline_Included
#define Y_Concurrent_Pipeline_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/container/sequence/list.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        typedef List<Kernel>   Kernels;
        typedef List<Task::ID> TaskIDs;


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

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________
            virtual void prune() noexcept = 0; //!< remove pending tasks
            virtual void flush() noexcept = 0; //!< wait for all tasks to be done

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        protected:
            Task::ID counter; //!< global task counter

        private:
            Y_Disable_Copy_And_Assign(Pipeline); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

