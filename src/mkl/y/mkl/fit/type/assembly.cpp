
#include "y/mkl/fit/type/assembly.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            Assembly:: Assembly() noexcept : maxNameSize(0)
            {
            }

            Assembly:: ~Assembly() noexcept
            {

            }

            void Assembly:: admit(const Entity &ent) noexcept
            {
                InSituMax( Coerce(maxNameSize), ent.name.size() );
            }

            


        }
    }

}
