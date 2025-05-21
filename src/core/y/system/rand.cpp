
#include "y/system/rand.hpp"
#include <ctime>
#include <cstdlib>

namespace Yttrium
{
    namespace System
    {
        Rand:: Rand() noexcept
        {
            srand( unsigned(time(0)) );
        }

        Rand:: ~Rand() noexcept
        {

        }

        template <>
        float Rand:: to<float>() noexcept
        {
            static const float denom = static_cast<float>(RAND_MAX)+1.0f;
            return ( static_cast<float>( rand() ) + 0.5f ) / denom;
        }

        template <>
        double Rand:: to<double>() noexcept
        {
            static const double denom = static_cast<double>(RAND_MAX)+1.0;
            return ( static_cast<double>( rand() ) + 0.5 ) / denom;
        }

        template <>
        long double Rand:: to<long double>() noexcept
        {
            static const long double denom = static_cast<long double>(RAND_MAX)+1.0L;
            return ( static_cast<long double>( rand() ) + 0.5L ) / denom;
        }

    }

}
