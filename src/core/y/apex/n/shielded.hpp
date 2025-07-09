//! \file

#ifndef Y_Apex_Shielded_Included
#define Y_Apex_Shielded_Included 1

#include "y/apex/number.hpp"
#include "y/apex/m/shield.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Shielded Number for Natural
        //
        //
        //______________________________________________________________________
        class Shielded : public Number
        {
        protected:
            explicit Shielded();          //!< setup
        public:
            virtual ~Shielded() noexcept; //!< cleanup

            Lockable & operator*() const noexcept; //!< \return mutex

        private:
            Y_Disable_Copy_And_Assign(Shielded); //!< discarding
            mutable Shield shield;               //!< internal shield
        };
    }
}

#endif
