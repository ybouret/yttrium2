//! \file

#ifndef Y_Calculus_IntegerSqrt_Included
#define Y_Calculus_IntegerSqrt_Included 1

#include "y/type/ints.hpp"
#include "y/type/is-signed.hpp"

namespace Yttrium
{

    namespace Calculus
    {
        //! integer square root algorithm
        struct IntegerSquareRoot
        {
            static void throwNegativeArg(); //!< error on negative input

            //! unsigned \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<false> &) noexcept
            {
                if(s<=1) return s;
                T x0 = s >> 1 ;
                while(true) {
                    const T x1 = (x0+s/x0)>>1;
                    if(x1>=x0) break;
                    x0 = x1;
                }
                return x0;
            }

            //! signed \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<true> &) noexcept
            {
                static const IntToType<false> Converted = {};
                if(s<0) throwNegativeArg();
                typedef typename UnsignedIntFor<T>::Result::Type U;
                return T( Compute<U>( U(s), Converted) );
            }

            typedef uint16_t       TableType;
            static const size_t    TableBytes = 65536;
            static const size_t    TableSize  = TableBytes/sizeof(TableType);
            static const TableType TableLast  = TableSize-1;
            static const TableType Table[TableSize];

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


