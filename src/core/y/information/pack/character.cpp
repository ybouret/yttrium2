#include "y/information/pack/character.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            void Character:: reset(const unsigned n, const FreqType f) noexcept
            {
                code = data;
                bits = n;
                freq = f;
                next = 0;
                prev = 0;
            }

            Character::FreqType Character:: reduce() noexcept
            {
                static const FreqType one = 1;
                assert(freq>0);
                return ( (freq >>= 1) |= one );
            }

        }

    }
}
