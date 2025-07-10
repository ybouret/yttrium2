
//! \file

#ifndef Y_Apex_Rational_Included
#define Y_Apex_Rational_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Rational : public Number
        {
        public:
            static const char * const CallSign;
            
            Rational();
            Rational(const Rational &);
            Rational & operator=(const Rational &);
            virtual ~Rational() noexcept;

            Rational(const integer_t,const natural_t);
            Rational(const Integer &);
            Rational(const Natural &);

            Y_OSTREAM_PROTO(Rational);

            virtual size_t serialize(OutputStream&) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;

            Rational &     xch(Rational &) noexcept;
            Rational &     neg() noexcept;


            const Integer numer;
            const Natural denom;

        private:
            void           simplify();

        };
    }

    typedef Apex::Rational apq;
}

#endif

