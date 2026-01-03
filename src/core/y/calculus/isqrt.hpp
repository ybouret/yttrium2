//! \file

#ifndef Y_Calculus_IntegerSqrt_Included
#define Y_Calculus_IntegerSqrt_Included 1

#include "y/type/ints.hpp"
#include "y/type/is-signed.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Calculus
    {
        //! integer square root algorithm
        struct IntegerSquareRoot
        {

            static const uint8_t  MaxResult = 255;
            static const uint16_t MaxValue_ = MaxResult;
            static const uint16_t MaxSquare = MaxValue_ * MaxValue_;
            static const uint64_t TableLast = MaxSquare;
            static const uint64_t TableSize = TableLast + 1;
            static const uint8_t  Table[TableSize];

            static void throwNegativeArg(); //!< error on negative input

        private:
            template <typename T> static inline
            T ComputeAbove2_(const T s) noexcept
            {
                assert(s>=2);
                T x0 = s >> 1 ;
                while(true) {
                    const T x1 = (x0+s/x0)>>1;
                    if(x1>=x0) break;
                    x0 = x1;
                }
                return x0;
            }
        public:

            //! full unsigned algorithm \param s argument \return isqrt(s)
            template <typename T> static inline
            T ComputeRegular(const T s) noexcept
            {
                return s<=1 ? s : ComputeAbove2_<T>(s);
            }

            //! table unsigned algorithm \param s argument \return isqrt(s)
            template <typename T> static inline
            T ComputeByTable(const T s) noexcept
            {
                const uint64_t s64 = s;
                return s64 <= TableLast ? Table[s64] : ComputeAbove2_<T>(s);

            }



            //! unsigned prototype \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<false> &) noexcept
            {
                return ComputeByTable(s);
            }

            //! signed prototype \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<true> &) noexcept
            {
                static const IntToType<false> Converted = {};
                if(s<0) throwNegativeArg();
                typedef typename UnsignedIntFor<T>::Result::Type U;
                return T( Compute<U>( U(s), Converted) );
            }

        };


    }

    //! integer square root \param s integral value \return isqrt
    template <typename T> inline
    T IntegerSquareRoot(const T s) noexcept
    {
        static const IntToType< IsSigned<T>::Value > Choice = {};
        return Calculus::IntegerSquareRoot::Compute(s,Choice);
    }

}

#endif // !Y_Calculus_IntegerSqrt_Included


