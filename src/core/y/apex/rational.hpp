
//! \file

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Rational : public Number
        {
        public:
            Rational();
            virtual ~Rational() noexcept;

            const Integer numer;
            const Natural denom;

        private:

        };
    }
}

#endif

