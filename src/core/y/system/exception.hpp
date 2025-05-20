
//! \file

#ifndef Y_System_Exception_Included
#define Y_System_Exception_Included 1

#include "y/exception.hpp"

namespace Yttrium
{
    namespace Specific
    {
        //__________________________________________________________________________
        //
        //
        //
        //! Information with specific reason
        //
        //
        //__________________________________________________________________________
        class Exception : public Yttrium::Exception
        {
        public:
            virtual ~Exception() noexcept;
            
        private:
            Y_Disable_Assign(Exception); //!< no assigment
        };
    }
}

#endif

