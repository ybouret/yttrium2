
//! \file

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"
#include "y/apex/q/helpers.hpp"

namespace Yttrium
{
    //! in-place fraction
    struct Fraction
    {
        int64_t  numer; //!< numerator
        uint64_t denom; //!< denominator
    };

    namespace Apex
    {
        
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
            Rational(const SignType, const Natural &, const Natural &); //!< numer(s,n), denom(d)

            Rational & operator=(const Natural &); //!< \return *this
            Rational & operator=(const Integer &); //!< \return *this
            Rational & operator=(const integer_t); //!< \return *this
            Rational & operator=(const Fraction);  //!< \return *this
            
            Rational(InputStream&,const char * const=0); //!< reload from saved state

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

            Y_APQ_Proto_Decl(static Rational,Sub);
            Y_APQ_Operator_Impl(-,Sub)

            Y_APQ_Proto_Decl(static Rational,Mul);
            Y_APQ_Operator_Impl(*,Mul)

            Y_APQ_Proto_Decl(static Rational,Div);
            Y_APQ_Operator_Impl(/,Div)

 #endif

            //__________________________________________________________________
            //
            //
            // Specific additions
            //
            //__________________________________________________________________
            Rational   operator+() const; //!< \return *this
            Rational & operator++();      //!< prefix  \return increased *this
            Rational   operator++(int);   //!< postfix \return previous value, increase *this
            void       incr();            //!< in-place increase

            //__________________________________________________________________
            //
            //
            // Specific subtraction
            //
            //__________________________________________________________________
            Rational   operator-() const; //!< \return - *this
            Rational & operator--();      //!< prefix  \return decreased *this
            Rational   operator--(int);   //!< postfix \return previous value, decrease *this*
            void       decr();            //!< in-place decrease


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
            // Members
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

