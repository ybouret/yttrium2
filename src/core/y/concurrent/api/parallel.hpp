
//! \file

#ifndef Y_Concurrent_Parallel_Included
#define Y_Concurrent_Parallel_Included 1

#include "y/ability/identifiable.hpp"

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
        class Parallel  : public Identifiable
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            explicit Parallel(const size_t, const char * const);

        public:
            //! cleanup
            virtual ~Parallel() noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t size; //!< number of contexts/threads

        private:
            Y_Disable_Copy_And_Assign(Parallel); //!< discarding
        };

    }


}

#endif // !Y_Concurrent_Parallel_Included

