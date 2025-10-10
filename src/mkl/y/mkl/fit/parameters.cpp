#include "y/mkl/fit/parameters.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Parameters:: ~Parameters() noexcept
            {
            }

            Parameters:: Parameters() : Ingress<const ParameterDB>(), db()
            {
            }

            Y_Ingress_Impl(Parameters,db)


            const char * const Parameters:: CallSign = "Fit::Parameters";

            Parameters & Parameters:: grow(const Parameter::Pointer &p)
            {
                if(!db.insert(p))
                    throw Specific::Exception(CallSign,"multiple parameter '%s'", p->name.c_str());
                return *this;
            }


        }
    }

}
