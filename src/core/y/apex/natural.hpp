
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
#include "y/mkl/xreal.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace Random { class Bits; }

    namespace Apex
    {

        Y_Shallow_Decl(Hook); //!< alias

        template <typename T> struct RealDigits;

        //! digits for float
        template <> struct RealDigits<float>       { static const unsigned Count = FLT_DIG; /*!< FLT_DIG */  };

        //! digits for double
        template <> struct RealDigits<double>      { static const unsigned Count = DBL_DIG;  /*!< DBL_DIG */};

        //! digits for long double
        template <> struct RealDigits<long double> { static const unsigned Count = LDBL_DIG; /*!< LDBL_DIG */};

        //! digits for associated XReal
        template <typename T> struct RealDigits< XReal<T> > { static const unsigned Count = RealDigits<T>::Count; /*!< alias */  };

        //! Mutliplication Algorithms
        enum MultiplicationAlgorithm
        {
            RegularMultiplication, //!< long multiplication
            FourierMultiplication  //!< dft multiplication
        };

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
            static const char * HumanReadableOps() noexcept; //!< \return current readable Ops

            typedef Device * (*MulProc1)(const Natural &, const Natural &); //!< alias
            typedef Device * (*MulProc2)(const Natural &, const natural_t); //!< alias
            typedef Device * (*MulProc3)(const natural_t, const Natural &); //!< alias
            typedef Device * (*SqrProc)(const Natural &);

            //! API for multiplication
            struct MulAPI
            {
                MulProc1 proc1; //!< function
                MulProc2 proc2; //!< function
                MulProc3 proc3; //!< function
                SqrProc  sproc; //!< function
            };

            static const MulAPI LMulAPI; //!< API for long multiplication
            static const MulAPI FMulAPI; //!< API for dft multiplication

            static MultiplicationAlgorithm Set(const MultiplicationAlgorithm) noexcept; //!< set new method \return old methods
            static MultiplicationAlgorithm Get() noexcept;                              //!< \return current method
            static const char *            MulAlgoName() noexcept;                      //!< \return humann readable method


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
            virtual size_t       serialize(OutputStream &) const;
            virtual const char * callSign()       const noexcept;
            virtual void         ldz()                  noexcept;
            virtual void         ld1()                  noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t         bits()   const noexcept; //!< \return current bits
            Natural &      xch(Natural &) noexcept; //!< \return no-throw exchanged
            uint64_t       ls64() const   noexcept; //!< \return least significant 64 bits
            size_t         bytes() const  noexcept; //!< \return current number of bytes


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
            Y_APN_Proto_Decl(static Device *,LMul);
            Y_APN_Proto_Decl(static Device *,FMul);
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
            Natural        sqr()       const; //!< \return |*this|^2
            Natural        abs()       const; //!< \return *this
            Natural        sqrt()      const; //!< \return integer square root
            String         hexString() const; //!< \return hexadecimal, concise string
            String         decString() const; //!< \return decimal string
            bool           isOdd()  const noexcept; //!< \return true iff odd
            bool           isEven() const noexcept; //!< \return true iff even


            static Natural GCD(const Natural &, const Natural &); //!< \return gcd(,)
            static Natural LCM(const Natural &, const Natural &); //!< \return least common multiple
            static void    Simplify(Natural &, Natural&);         //!< atomic simplification
            static Natural Factorial(const size_t);               //!< \return n!
            static Natural Comb(const size_t n, const size_t k);  //!< \param n n>=0 \param k k<=m \return (n,k)
            static Natural Enum(const size_t n, const size_t k);  //!< \param n n>=0 \param k k<=n \return enumerations of k-uplets of n items

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

            //! cast \param varName optional variable name \return casted when possible
            template <typename T> inline
            T cast(const char * const varName = 0) const
            {
                T res(0);
                if(!tryCast(res)) castOverflow(varName);
                return res;
            }

            //! \param num numerator \param den denominator \return ratio with given precision
            template <typename T> static inline
            T Ratio(const Natural &num, const Natural &den)
            {
                static const unsigned  Digits = RealDigits<T>::Count;
                static const T         Factor = 256;
                static const T         Tenth  = 0.1;
                static const natural_t ten    = 10;
                Natural N = num;
                Natural q,r;

                T res = 0;

                // integer part
                Div_(&q,&r,N,den);
                {
                    const uint8_t * const b = q.data8();
                    size_t                n = q.bytes();
                    while(n-- > 0 )
                    {
                        res *= Factor;
                        res += b[n];
                    }
                }

                T pos = Tenth;
                for(unsigned i=0;i<Digits;++i, pos *= Tenth)
                {
                    if(r.bits()<=0) break;
                    N.xch(r);
                    N *= ten;
                    Div_(&q,&r,N,den);
                    res += pos * static_cast<T>(q.data8()[0]);
                }

                return res;
            }


        private:
            Natural(const Hook_ &, Device *); //!< direct construction

            //! \return this as bytes, without locking
            const uint8_t * data8() const noexcept;

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

            static Device * LSqr(const Natural &);
            static Device * FSqr(const Natural &);


        };
    }
    
    typedef Apex::Natural apn; //!< alias
}

#endif
