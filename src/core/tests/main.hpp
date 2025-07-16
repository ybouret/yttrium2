#ifndef MAIN_Included
#define MAIN_Included

#include "y/mkl/complex.hpp"
#include "y/random/in3d.hpp"
#include "y/random/in2d.hpp"
#include "y/random/mt19937.hpp"
#include "y/apex/rational.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{

    template <typename>
    struct Gen;

    template <typename T>
    struct Gen
    {
        static inline T New(Random::Bits &ran)
        {
            return ran.symm<T>();
        }
    };

    template <typename T>
    struct Gen< Complex<T> >
    {
        static inline Complex<T> New(Random::Bits &ran)
        {
            return Random::InDisk< Complex<T> >(ran);
        }
    };

    template <typename T>
    struct Gen< V2D<T> >
    {
        static inline V2D<T> New(Random::Bits &ran)
        {
            return Random::InDisk< V2D<T>  >(ran);
        }
    };

    template <typename T>
    struct Gen< V3D<T> >
    {
        static inline V3D<T> New(Random::Bits &ran)
        {
            return Random::InBall< V3D<T>  >(ran);
        }
    };

    template <>
    struct Gen<apn>
    {
        static const size_t MaxBits = 20;

        static inline size_t bits(Random::Bits &ran) noexcept
        {
            return ran.leq<size_t>(MaxBits);
        }

        static inline apn New(Random::Bits &ran)
        {
            return apn(ran,bits(ran));
        }
    };

    template <>
    struct Gen<apz>
    {
        static inline apz New(Random::Bits &ran)
        {
            return apz(ran,Gen<apn>::bits(ran));
        }
    };

    template <>
    struct Gen<apq>
    {
         static inline apq New(Random::Bits &ran)
        {
             return apq(ran,Gen<apn>::bits(ran), Max<size_t>(1,Gen<apn>::bits(ran)));
        }
    };



}

#endif

