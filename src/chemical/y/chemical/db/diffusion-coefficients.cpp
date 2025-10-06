
#include "y/chemical/db/diffusion-coefficients.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char DiffusionCoefficients:: JSDict[] =
        {
#include "diffusion-coefficients.hxx"
        };

        const size_t DiffusionCoefficients:: Length = sizeof(JSDict);

        const double DiffusionCoefficients:: SI = 1e-9;
    }
}

