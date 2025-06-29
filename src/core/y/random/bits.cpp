
#include "y/random/bits.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Random
    {

        class Bits:: Metrics : public Object
        {
        public:
            explicit Metrics(const uint32_t highest32) noexcept :
            Object(),
            upper(highest32),
            denom( static_cast<Real>(upper) + Real(1.0) )
            {
            }

            virtual ~Metrics() noexcept {}

            const uint32_t upper;
            const Real     denom;

        private:
            Y_Disable_Copy_And_Assign(Metrics);
        };

        Bits:: Bits(const uint32_t highest32) noexcept :
        metrics( new Metrics(highest32) )
        {
        }

        Bits:: ~Bits() noexcept
        {
            Destroy(metrics);
        }

    }
}
