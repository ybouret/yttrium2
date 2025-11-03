
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

            //! process all pending tasks
            virtual void flush() noexcept = 0;

            //! remove all pending tasks
            virtual void purge() noexcept = 0;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! create and enqueue a new task
            /**
             \param fcn callable, Kernel...
             \return task ID
             */
            template <typename CALLABLE> inline
            Task::ID enqueue(const CALLABLE &fcn)
            {
                enqueueTask( new Task(fcn,counter) );
                return counter++;
            }

            //! create and enqueue a new task
            /**
             \param host persistent host reference
             \param meth host method
             \return task ID
             */
            template <typename OBJECT, typename METHOD> inline
            Task::ID enqueue(OBJECT & host,
                             METHOD   meth)
            {
                enqueueTask( new Task(host,meth,counter) );
                return counter++;
            }


            void batch(Task::Dict  & dict,
                       const Batch & todo);

            Task::Status query(const Task::ID) const noexcept;

            //! query remaining tasks
            /**
             \param dict dictionary from batch
             \return new dict size
             */
            size_t prune(Task::Dict &dict) const noexcept;

        protected:
            Task::ID counter; //!< global task counter

        private:
            Y_Disable_Copy_And_Assign(Pipeline); //!< discarding


            //! enqueue a new task
            virtual void enqueueTask(Task * const) noexcept = 0;

            //! enqueue a batch of kernels
            /**
             \param dict dictionary of tasks
             \param todo pre-compiled kernels
             */
            virtual void enqueueBand(Task::Dict &             dict,
                                     const Readable<Kernel> & todo) = 0;


            virtual Task::Status getUnlocked(const Task::ID) const noexcept = 0;
            virtual Lockable &   getLockable()               const noexcept = 0;

        };
    }

}

#endif // !Y_Concurrent_Pipeline_Included

