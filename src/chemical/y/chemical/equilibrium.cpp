#include "y/chemical/equilibrium.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        const char * const Equilibrium:: CallSign = "Equilibrium";
       

        Equilibrium:: ~Equilibrium() noexcept
        {
        }

        xreal_t Equilibrium:: K(const xreal_t t)
        {
            const xreal_t k = getK(t);
            if(k<0.0) throw Specific::Exception(name.c_str(),"invalid constant @t=%g", real_t(t) );
            return k;
        }

    }


}

namespace Yttrium
{
    namespace Chemical
    {
        xreal_t ConstEquilibrium:: getK(const xreal_t)
        {
            return K_;
        }

        ConstEquilibrium:: ~ConstEquilibrium() noexcept
        {
        }
        
    }

}
