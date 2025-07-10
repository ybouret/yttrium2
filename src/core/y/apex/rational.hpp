
//! \file

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
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

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream&) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Rational &     xch(Rational &) noexcept; //!< exchange \return *this
            Rational &     neg() noexcept;           //!< in-place opposite \return *this


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

