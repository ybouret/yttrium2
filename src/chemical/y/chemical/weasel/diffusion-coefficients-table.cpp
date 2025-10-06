
#include "diffusion-coefficients-table.hpp"
#include "y/json/compiler.hpp"
#include "y/chemical/db/diffusion-coefficients.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Weasel:: DiffusionCoefficientsTable:: ~DiffusionCoefficientsTable() noexcept
        {
        }

        Weasel:: DiffusionCoefficientsTable:: DiffusionCoefficientsTable() :
        jv()
        {
            JSON::Compiler json;
            {
                Jive::Source   source( Jive::Module::OpenData("DiffusionCoefficients",
                                                              DiffusionCoefficients::JSDict,
                                                              DiffusionCoefficients::Length) );
                json(Coerce(jv),source);
            }

        }
    }
}
