
#include "y/mkl/tao/2.hpp"

namespace Yttrium
{
    namespace  MKL
    {

        namespace Tao
        {

            LinearBroker:: LinearBroker(const LinearEngine &lp) :
            engine(lp)
            {
                engine->acquireLocalMemory( sizeof(void*) );
            }

            LinearBroker:: ~LinearBroker() noexcept
            {
            }


        }
    }
}
