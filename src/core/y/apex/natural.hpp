
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/apex/k/ops.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/apex/k/plan.hpp"
#include "y/type/sign.hpp"
#include "y/apex/n/shielded.hpp"
#include "y/apex/n/smartdev.hpp"
#include "y/string.hpp"
#include "y/type/is-signed.hpp"

#include "y/apex/n/helpers.hpp"

namespace Yttrium
{
    namespace Random { class Bits; }

    namespace Apex
    {

        Y_Shallow_Decl(Hook); //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Natural number
        //
        //
        //______________________________________________________________________
        class Natural : public SmartDev, public Shielded
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static OpsMode            Ops;      //!< for multiplication/division
            static PlanType           Cmp;      //!< for comparisons
            static PlanType           BWO;      //!< for BitWise Ops
            static const char * const CallSign; //!< "apn"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Natural();                                     //!< setup empty
            virtual ~Natural() noexcept;                   //!< cleanup
            Natural(const Natural &);                      //!< duplicate
            Natural & operator=(const Natural &);          //!< \return assigned by copy/swap
            Natural(const natural_t);                      //!< setup
            Natural & operator=(const natural_t) noexcept; //!< \return assigned
            Y_OSTREAM_PROTO(Natural);                      //!< display hex/dec

            Natural(Random::Bits & , const size_t);           //!< setup with exact number of random bits
            Natural(const TwoToThePowerOf_ &, const size_t ); //!< setup to 2^n
            Natural(InputStream &, const char * const = 0 );  //!< load from input stream

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream &) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t         bits()   const noexcept; //!< \return current bits
            Natural &      xch(Natural &) noexcept; //!< \return no-throw exchanged
            uint64_t       ls64() const   noexcept; //!< \return least significant 64 bits

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_APN_Proto_Decl_NoExcept(static SignType,Compare);
            Y_APN_Compare_Decl(==, == __Zero__)
            Y_APN_Compare_Decl(!=, != __Zero__)
            Y_APN_Compare_Decl(<,  == Negative)
            Y_APN_Compare_Decl(>,  == Positive)
            Y_APN_Compare_Decl(<=, != Positive)
            Y_APN_Compare_Decl(>=, != Negative)

            Y_APN_Proto_Decl(static Device *,Add);
            Y_APN_Operator_Impl(+,Add)

            Y_APN_Proto_Decl(static Device *,Sub);
            Y_APN_Operator_Impl(-,Sub)

            Y_APN_Proto_Decl(static Device *,Mul);
            Y_APN_Operator_Impl(*,Mul)
            Y_APN_DivMod_Impl(/,Div)
            Y_APN_DivMod_Impl(%,Mod)
#endif

            //__________________________________________________________________
            //
            //
            // Specific additions
            //
            //__________________________________________________________________
            Natural   operator+() const; //!< \return *this
            Natural & operator++();      //!< prefix  \return increased *this
            Natural   operator++(int);   //!< postfix \return previous value, increase *this*
            void      incr();            //!< in-place increase

            //__________________________________________________________________
            //
            //
            // Specific subtraction
            //
            //__________________________________________________________________
            Natural & operator--();      //!< prefix  \return decreased *this
            Natural   operator--(int);   //!< postfix \return previous value, decrease *this*
            void      decr();            //!< in-place decrease

            //__________________________________________________________________
            //
            //
            // flexible div
            //
            //__________________________________________________________________

            //! ldiv for natural
            /**
             \param Q optional quot
             \param R optional rem
             \param numer numerator
             \param denom denominator
             */
            static void Div_(Natural * const Q,
                             Natural * const R,
                             const Natural  &numer,
                             const Natural  &denom);
            
            static Natural Div(const Natural & , const Natural & ); //!< \return divison
            static Natural Mod(const Natural & , const Natural & ); //!< \return modulus

            //__________________________________________________________________
            //
            //
            // algebra
            //
            //__________________________________________________________________
            void           shr()    noexcept; //!< in-place shr
            Natural        abs()       const; //!< \return *this
            Natural        sqrt()      const; //!< \return integer square root
            String         hexString() const; //!< \return hexadecimal, concise string
            String         decString() const; //!< \return decimal string

            static Natural GCD(const Natural &, const Natural &); //!< \return gcd(,)
            static Natural LCM(const Natural &, const Natural &); //!< \return least common multiple
            static void    Simplify(Natural &, Natural&);         //!< atomic simplification
            static Natural Factorial(const size_t);               //!< \return n!
            static Natural Comb(const size_t n, const size_t k);  //!< \param n n>=0 \param k k<=m \return (n,k)

            //! try cast to integral value
            /**
             \param value target value
             \return true if compatible
             */
            template <typename T> inline
            bool tryCast(T &value) const noexcept
            {
                static const IntToType< IsSigned<T>::Value > choice = {};
                return tryCast(value,choice);
            }


        private:
            Natural(const Hook_ &, Device *); //!< direct construction

            //! unsigned try cast \param value unsigned target \return true if possible
            template <typename T> inline
            bool tryCast(T &value, const IntToType<false> &) const noexcept
            {
                const size_t MaxBits = sizeof(T) * 8;
                if( bits() > MaxBits ) return false;
                value = T( ls64() );
                return true;
            }

            //! signed try cast \param value signed target \return true if possible
            template <typename T> inline
            bool tryCast(T &value, const IntToType<true> &) const noexcept
            {
                const size_t MaxBits = sizeof(T) * 8-1;
                if( bits() > MaxBits ) return false;
                value = T( ls64() );
                return true;
            }

        };
    }
    
    typedef Apex::Natural apn; //!< alias
}

#endif
