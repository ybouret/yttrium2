
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

    SignType Sign:: Opposite(const SignType s) noexcept
    {
        switch(s)
        {
            case __Zero__: break;
            case Positive: return Negative;
            case Negative: return Positive;
        }
        return __Zero__;
    }

    void Sign:: MakeOpposite(SignType &s) noexcept
    {
        s = Opposite(s);
    }

    bool Sign:: AreOpposite(const SignType lhs ,const SignType rhs) noexcept
    {
        return (lhs == Negative && rhs == Positive) || (lhs == Positive && rhs == Negative);
    }


    Sign::PairType Sign:: Pair(const SignType l, const SignType r) noexcept
    {
        switch(l)
        {
            case Negative: // prefix N
                switch(r)
                {
                    case Negative: return NN;
                    case __Zero__: return NZ;
                    case Positive: return NP;
                }
                break;

            case __Zero__: // prefix Z
                switch(r)
                {
                    case Negative: return ZN;
                    case __Zero__: break;
                    case Positive: return ZP;
                }
                break;

            case Positive: // prefix P
                switch(r)
                {
                    case Negative: return PN;
                    case __Zero__: return PZ;
                    case Positive: return PP;
                }

        }
        assert(__Zero__==l); assert(__Zero__==r);
        return ZZ;
    }

}

