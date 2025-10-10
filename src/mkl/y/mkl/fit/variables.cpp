

#include "y/mkl/fit/variables.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Variables:: ~Variables() noexcept
            {
            }


            Variables:: Variables() : Ingress<const VariableDB>(), db()
            {
            }

            Y_Ingress_Impl(Variables,db)
        }

    }

}
