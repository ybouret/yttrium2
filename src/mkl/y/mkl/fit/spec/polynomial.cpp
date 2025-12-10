
#include "y/mkl/fit/spec/polynomial.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Polynomial:: Coefficients:: ~Coefficients() noexcept {}

            Y_Ingress_Impl(Polynomial::Coefficients,parameters)


            Polynomial:: Coefficients &  Polynomial:: Coefficients :: operator<<(const size_t degree)
            {

                const String name = root + Decimal(degree).c_str();

                if(!parameters->search(name))
                {
                    parameters << name;
                }


                return *this;
            }

        }
    }
}

