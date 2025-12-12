
#include "y/mkl/fit/spec/polynomial.hpp"
#include "y/format/decimal.hpp"

#include "y/exception.hpp"
#include "y/ascii/convert.hpp"

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


            Polynomial::Coefficients:: Coefficients(const Coefficients &coef) :
            Ingress<const Parameters>(),
            root(coef.root),
            parameters(coef.parameters)
            {

            }


            static const char * const CallSign = "Polynomial::Coefficients";
            
            size_t  Polynomial::Coefficients:: degreeOf(const Parameter &p) const
            {
                const String &     name = p.name;
                const char * const uuid = name.c_str();
                if(name.size()<=root.size()) throw Specific::Exception(CallSign,"invalid name '%s'", uuid);
                const char * const data = uuid + root.size();
                return ASCII::Convert::To<size_t>(data,uuid);

            }


        }
    }
}

