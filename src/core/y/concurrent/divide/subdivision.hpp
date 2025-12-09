//! \file


#ifndef Y_Concurrent_Subdivision_Included
#define Y_Concurrent_Subdivision_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Generic subdivision interface
        //
        //
        //______________________________________________________________________
        class Subdivision
        {
        public:
            static const char * const Empty; //!< "|empty|";


        protected:
            explicit Subdivision() noexcept; //!< setup

        public:
            virtual ~Subdivision() noexcept; //!< cleanup

            virtual bool isEmpty() const noexcept = 0;
            
        private:
            Y_Disable_Copy_And_Assign(Subdivision); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Subdivision_Included
