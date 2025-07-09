
#include "y/apex/integer.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{

    namespace Apex
    {


        Integer Integer:: Div(const Integer &lhs, const Integer &rhs)
        {

            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ:
                case Sign::NZ:
                case Sign::PZ:
                    throw Libc::Exception(EDOM,"division by zero %s", CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // zero

                case Sign::NN:
                case Sign::PP: { const Natural q = lhs.n/rhs.n; return Integer(Positive,q); }
                case Sign::NP:
                case Sign::PN: { const Natural q = lhs.n/rhs.n; return Integer(Negative,q); }
            }

            return Integer();
        }

    }

}

