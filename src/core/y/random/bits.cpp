
#include "y/random/bits.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/hexadecimal.hpp"
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
            denom( static_cast<Real>(upper) + Real(1.0) ),
            nbits( BitsFor(upper) ),
            midst( upper >> 1 )
            {
                //std::cerr << "upper=" << Hexadecimal(upper) << std::endl;
                //std::cerr << "nbits=" << nbits << std::endl;
            }

            virtual ~Metrics() noexcept {}

            const uint32_t upper;
            const Real     denom;
            const unsigned nbits;
            const uint32_t midst;

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

        Bits::Real Bits:: real32() noexcept
        {
            static const Real half(0.5);
            return ( static_cast<Real>( next32() ) + half ) / metrics->denom;
        }

        Bits::Real Bits:: symm32() noexcept
        {
            static const Real half(0.5);
            const Real x = real32() - half;
            return x+x;
        }


        bool Bits:: choice() noexcept
        {
            return next32() <= metrics->midst;
        }

        uint64_t Bits:: fill64(const size_t nbit) noexcept
        {
            uint64_t result    = 0;
            size_t   remaining = nbit;
            while(remaining>0)
            {
                uint32_t dword     = next32();
                size_t   available = metrics->nbits;
                if(remaining<=available)
                {
                    // enough bits
                    result <<= remaining;
                    dword  >>= (available-remaining);
                    result |= dword;
                    break;
                }
                else
                {
                    // not enough bits
                    assert(remaining>available);
                    result <<= available;
                    result  |= dword;
                    remaining -= available;
                }
            }
            return result;
        }



    }
}
