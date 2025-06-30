//! \file

#ifndef Y_Random_Bits_Included
#define Y_Random_Bits_Included 1

#include "y/ability/serializable.hpp"
#include "y/ability/identifiable.hpp"
#include "y/mkl/xreal.hpp"
#include "y/type/alternative.hpp"
#include "y/type/traits.hpp"
#include "y/type/is-signed.hpp"
#include <cassert>
#include <cmath>

namespace Yttrium
{
    namespace Random
    {

        //______________________________________________________________________
        //
        //
        //
        //! interface to random bits
        //
        //
        //______________________________________________________________________
        class Bits : public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class               Metrics;
            typedef long double Real;     //!< alias

            typedef TL6(float,double,long double,XReal<float>,XReal<double>,XReal<long double>) FPList;

            //enum { IsIsoFloatingPoint   = ( TL::IndexOf<TL::IsoFloatingPoint,T>::Value >= 0 ) };
        protected:
            //! setup \param highest32 higest reached 32-bits value
            explicit Bits(const uint32_t highest32) noexcept;

        public:
            virtual ~Bits() noexcept; //!< cleanup
            //__________________________________________________________________
            //
            //
            //  Interface
            //
            //__________________________________________________________________
            virtual uint32_t next32() noexcept = 0; //!< \return next 32-bits value

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Real             real32() noexcept;                  //!< convert uint32_t \return floating point in ]0:1[
            uint64_t         fill64(const size_t nbit) noexcept; //!< \param nbit number of bits \return truncated uint64_t with nbit
            bool             choice() noexcept;                  //!< \return equiprobable choice

            //! \return any floating point in ]0:1[
            template <typename T> inline T toR() noexcept { return static_cast<T>( real32() ); }

            //! \return any unsigned integral value
            template <typename T> inline T toU() noexcept
            {
                return static_cast<T>( fill64(sizeof(T)*8) );
            }

            //! \return any signed integral value
            template <typename T> inline T toS() noexcept
            {
                const T u = static_cast<T>( fill64(sizeof(T)*8-1) );
                return choice() ? -u : u;
            }

        private:
            enum IntrinsicType
            {
                Floating,
                Integral
            };

        public:

            //! \return return selected random type
            template <typename T>
            T to() noexcept
            {
                static const typename Pick<TL::IndexOf<FPList,T>::Value >= 0 , IntToType<Floating>, IntToType<Integral> >::Type Choice = {};
                return intrinsic<T>(Choice);
            }



            //! \param nbit bit count \return unsigned with exact bit count
            template <typename T>
            T to(const size_t nbit) noexcept
            {
                assert(nbit<=sizeof(T)*8);
                assert(!IsSigned<T>::Value);
                static const T one = 1;
                if(nbit<=0) return 0;
                T res = one;
                for(size_t i=nbit-1;i>0;--i)
                {
                    res <<= 1;
                    if( choice() ) res |= one;
                }
                return res;
            }

            //! return uniform in [0:n] \param n >= 0
            template <typename T> inline
            T leq(const T n) noexcept
            {
                static const Real half(0.5);
                return static_cast<T>(std::floor( Real(n) * real32() + half ));
            }

            //! return uniform in [0:n-1] \param n > 0
            template <typename T> inline
            T lt(const T n) noexcept
            {
                assert(n>0);
                return leq(n-1);
            }

            template <typename T> inline
            T in(const T a, const T b) noexcept
            {
                assert(b>=a);
                return a + leq(b-a);
            }


        private:
            Y_Disable_Copy_And_Assign(Bits); //!< discarding
            Metrics * const metrics;         //!< internal metrics

            template <typename T> inline
            T intrinsic( const IntToType<Floating> & ) noexcept
            {
                return toR<T>();
            }

            template <typename T> inline
            T intrinsic( const IntToType<Integral> & ) noexcept
            {
                static const IntToType< IsSigned<T>::Value > Choice = {};
                return to<T>( Choice );
            }
            template <typename T> inline T to( const IntToType<false> & ) noexcept { return toU<T>(); } //!< \return unsigned
            template <typename T> inline T to( const IntToType<true>  & ) noexcept { return toS<T>(); } //!< \return signed

        };



    }
}

#endif

