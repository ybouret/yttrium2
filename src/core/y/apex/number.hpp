

#ifndef Y_Apex_Number_Included
#define Y_Apex_Number_Included 1

#include "y/ability/serializable.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! base class for numbers
        //
        //
        //______________________________________________________________________
        class Number : public Serializable
        {
        protected:
            explicit Number() noexcept; //!< setup

        public:
            virtual ~Number() noexcept; //!< cleanup

            virtual void   ldz()       noexcept = 0; //!< noexcept set to zero
            virtual void   ld1()       noexcept = 0; //!< noexcept set to one
            
        private:
            Y_Disable_Copy_And_Assign(Number); //!< discarding
        };
    }

}

#endif

