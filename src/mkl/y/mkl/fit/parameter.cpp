

#include "y/mkl/fit/parameter.hpp"
#include "y/string/env.hpp"
#include "y/string/boolean.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Parameter:: ~Parameter() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Parameter &p)
            {
                return os << p.name << "@" << p.indx;
            }

            bool Parameter:: queryEnv() const
            {
                String value;
                if( Environment::Get(value,name) )
                {
                    return StringToBoolean::Get(value,name.c_str());
                }
                else
                {
                    return true;
                }
            }

        }
    }

}


