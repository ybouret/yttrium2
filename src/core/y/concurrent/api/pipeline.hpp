
//! \file

#ifndef Y_Concurrent_Pipeline_Included
#define Y_Concurrent_Pipeline_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        class Task : public Kernel
        {
        public:
            typedef uint32_t ID;

            template <typename CALLABLE> inline
            explicit Task(const CALLABLE &fcn,
                          const ID        tid) :
            Kernel(fcn),
            uuid(tid),
            next(0),
            prev(0)
            {
            }
            

            virtual ~Task() noexcept {}

            const uint32_t uuid;
            Task *         next;
            Task *         prev;

        private:
            Y_Disable_Copy_And_Assign(Task);
        };

        typedef CxxListOf<Task> Tasks;


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
            // Interface
            //
            //__________________________________________________________________

        private:
            Y_Disable_Copy_And_Assign(Pipeline); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

