
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


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void flush() noexcept = 0;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            template <typename CALLABLE> inline
            Task::ID enqueue(const CALLABLE &fcn)
            {
                enqueueTask( new Task(fcn,counter) );
                return counter++;
            }

            template <typename OBJECT, typename METHOD> inline
            Task::ID enqueue(OBJECT & host,
                             METHOD   meth)
            {
                enqueueTask( new Task(host,meth,counter) );
                return counter++;
            }



        private:
            Y_Disable_Copy_And_Assign(Pipeline); //!< discarding
            Task::ID counter;
            virtual void enqueueTask(Task * const) noexcept = 0;
        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

