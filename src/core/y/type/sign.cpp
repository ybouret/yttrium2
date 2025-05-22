
#include "y/type/sign.hpp"

namespace Yttrium
{
    const char * Sign:: HumanReadable(const SignType s) noexcept
    {
        switch(s)
        {
                Y_Return_Named_Case(Negative);
                Y_Return_Named_Case(__Zero__);
                Y_Return_Named_Case(Positive);
        }
        return Core::Unknown;
    }
}

