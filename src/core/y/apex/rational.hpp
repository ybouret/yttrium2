
//! \file

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    struct Fraction
    {
        int64_t  numer;
        uint64_t denom;
    };

    namespace Apex
    {
        //! helper
#define Y_APQ_Proto_Decl(RET,FUNC)            \
RET FUNC(const Rational &, const Rational &); \
RET FUNC(const Rational &, const Integer  &); \
RET FUNC(const Integer  &, const Rational &); \
RET FUNC(const Rational &, const Natural  &); \
RET FUNC(const Natural  &, const Rational &); \
RET FUNC(const Rational &, const integer_t ); \
RET FUNC(const integer_t , const Rational &)

        //! helper
#define Y_APQ_Compare_Proto(OP,LHS,RHS,RET) \
inline friend bool operator OP (const LHS lhs, const RHS rhs) noexcept { return Compare(lhs,rhs) RET; }


        //! helper
#define Y_APQ_Compare_Decl(OP,RET) \
Y_APN_Compare_Proto(OP,Rational &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, Integer  &,RET) \
Y_APN_Compare_Proto(OP,Integer  &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, Natural  &,RET) \
Y_APN_Compare_Proto(OP,Natural  &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, integer_t ,RET) \
Y_APN_Compare_Proto(OP,integer_t , Rational &,RET)


        //! helper
#define Y_APQ_Operator_Proto_Binary(OP,LHS,RHS,CALL) \
inline friend Rational operator OP (const LHS lhs, const RHS rhs) { return CALL(lhs,rhs); }

        //! helper
#define Y_APQ_Operator_Impl_Binary(OP,CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Integer &, CALL)  \
Y_APQ_Operator_Proto_Binary(OP, Integer  &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Natural &, CALL)  \
Y_APQ_Operator_Proto_Binary(OP, Natural  &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, integer_t,  CALL) \
Y_APQ_Operator_Proto_Binary(OP, integer_t,  Rational &, CALL)

        //! helper
#define Y_APQ_Operator_Proto_Unary(OP,RHS,CALL) \
inline Rational & operator OP##=(const RHS rhs) { Rational res( CALL(*this,rhs) ); return xch(res); }


        //! helper
#define Y_APQ_Operator_Impl_Unary(OP,CALL)       \
Y_APQ_Operator_Proto_Unary(OP, Rational &, CALL) \
Y_APQ_Operator_Proto_Unary(OP, Integer  &, CALL) \
Y_APQ_Operator_Proto_Unary(OP, integer_t,  CALL) \
Y_APQ_Operator_Proto_Unary(OP, Natural &,  CALL)

        //! helper
#define   Y_APQ_Operator_Impl(OP,CALL) \
Y_APQ_Operator_Impl_Binary(OP,CALL)    \
Y_APQ_Operator_Impl_Unary(OP,CALL)

        //______________________________________________________________________
        //
        //
        //
        //! Rational Number
        //
        //
        //______________________________________________________________________
        class Rational : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "apq"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Rational();                                //!< setup
            Rational(const Rational &);                //!< duplicate
            Rational & operator=(const Rational &);    //!< assign \return *this
            virtual ~Rational() noexcept;              //!< cleanup
            Rational(const integer_t,const natural_t); //!< setup
            Rational(const Integer &);                 //!< setup
            Rational(const Natural &);                 //!< setup
            Y_OSTREAM_PROTO(Rational);                 //!< display
            Rational(const Fraction &);                //!< setup
            Rational(const Integer &,const Natural &); //!< setup
            Rational(const integer_t);                 //!< setup
            Rational(Random::Bits &,const size_t, const size_t); //!< random


            Rational & operator=(const Natural &); //!< \return *this
            Rational & operator=(const Integer &); //!< \return *this
            Rational & operator=(const integer_t); //!< \return *this
            Rational & operator=(const Fraction);  //!< \return *this

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream&) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_APQ_Proto_Decl(static SignType,Compare);
            Y_APQ_Compare_Decl(==, == __Zero__)
            Y_APQ_Compare_Decl(!=, != __Zero__)
            Y_APQ_Compare_Decl(<,  == Negative)
            Y_APQ_Compare_Decl(>,  == Positive)
            Y_APQ_Compare_Decl(<=, != Positive)
            Y_APQ_Compare_Decl(>=, != Negative)

            Y_APQ_Proto_Decl(static Rational,Add);
            Y_APQ_Operator_Impl(+,Add)
 #endif

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Rational &     xch(Rational &) noexcept; //!< exchange \return *this
            Rational &     neg() noexcept;           //!< in-place opposite \return *this
            Rational       abs() const;              //!< \return |*this|

            //__________________________________________________________________
            //
            //
            // Memberss
            //
            //__________________________________________________________________
            const Integer numer; //!< numerator
            const Natural denom; //!< denominator

        private:
            void           simplify(); //!< check/simplify

        };
    }

    typedef Apex::Rational apq; //!< alias
}

#endif

