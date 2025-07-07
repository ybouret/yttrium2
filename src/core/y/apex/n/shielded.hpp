//! \file

#ifndef Y_Apex_Shielded_Included
#define Y_Apex_Shielded_Included 1

#include "y/apex/number.hpp"
#include "y/apex/m/shield.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Shielded : public Number
        {
        protected:
            explicit Shielded();
        public:
            virtual ~Shielded() noexcept;

            Lockable & operator*() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(Shielded);
            mutable Shield shield;
        };
    }
}

#endif
