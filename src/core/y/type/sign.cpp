
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

    bool Sign:: StriclyIncreasing(const SignType s) noexcept
    {
        switch(s)
        {
            case Negative: return true;
            case __Zero__:
            case Positive:
                break;
        }
        return false;
    }

    bool Sign:: LooselyIncreasing(const SignType s) noexcept
    {
        switch(s)
        {
            case Positive: return false;
            case __Zero__:
            case Negative:
                break;
        }
        return true;
    }

    bool Sign:: StriclyDecreasing(const SignType s) noexcept
    {
        switch(s)
        {
            case Positive: return true;
            case __Zero__:
            case Negative:
                break;
        }
        return false;
    }

    bool Sign:: LooselyDecreasing(const SignType s) noexcept
    {
        switch(s)
        {
            case Negative: return false;
            case __Zero__:
            case Positive:
                break;
        }
        return true;
    }

}

