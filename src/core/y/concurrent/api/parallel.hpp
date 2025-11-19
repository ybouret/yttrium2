
//! \file

#ifndef Y_Concurrent_Parallel_Included
#define Y_Concurrent_Parallel_Included 1

#include "y/ability/identifiable.hpp"
#include "y/container.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base type for parallel objects
        //
        //
        //______________________________________________________________________
        class Parallel  : public Identifiable, public Container
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            explicit Parallel() noexcept;

        public:
            //! cleanup
            virtual ~Parallel() noexcept;


        private:
            Y_Disable_Copy_And_Assign(Parallel); //!< discarding
        };

    }


}

#endif // !Y_Concurrent_Parallel_Included

