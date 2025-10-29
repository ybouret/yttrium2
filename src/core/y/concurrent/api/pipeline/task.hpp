
//! \file

#ifndef Y_Concurrent_Task_Included
#define Y_Concurrent_Task_Included 1

#include "y/concurrent/api/kernel.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Task for Pipeline
        //
        //
        //______________________________________________________________________
        class Task : public Kernel
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef uint32_t ID; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param fcn callable \param tid task ID
            template <typename CALLABLE> inline
            explicit Task(const CALLABLE &fcn,
                          const ID        tid) :
            Kernel(fcn),
            uuid(tid),
            next(0),
            prev(0)
            {
            }

            //! setup \param host persistent host \param meth method \param tid task ID
            template <typename OBJECT, typename METHOD> inline
            explicit Task(OBJECT & host,
                          METHOD   meth,
                          const ID tid) :
            Kernel(&host,meth),
            uuid(tid),
            next(0),
            prev(0)
            {
            }

            //! cleanup
            virtual ~Task() noexcept;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! perform kernel
            void perform(const Context &) noexcept;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t uuid; //!< identifier from pipeline
            Task *         next; //!< for list
            Task *         prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(Task); //!< discarding
        };

        typedef CxxListOf<Task> Tasks; //!< alias

    }

}

#endif // !Y_Concurrent_Task_Included
