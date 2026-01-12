#include "y/information/pack/character.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            void Character:: reset(const unsigned n) noexcept
            {
                code = data;
                bits = n;
                freq = 0;
                next = 0;
                prev = 0;
            }

            Character::FreqType Character:: reduce() noexcept
            {
                static const FreqType one = 1;
                return freq <= 0 ? 0 :( (freq >>= 1) |= one );
            }

        }

    }
}
