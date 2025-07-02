
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    
    namespace Apex
    {

        //! Integer = signed natural
        class Integer : public Number
        {
        public:
            static const char Mark__Zero__ = 0x0;
            static const char MarkPositive = 0x1;
            static const char MarkNegative = 0x2;

            Integer();
            virtual ~Integer() noexcept;
            Integer(const Integer &);
            Integer & operator=(const Integer &);
            Y_OSTREAM_PROTO(Integer);

            Integer(const Natural &);
            Integer(const integer_t);
            Integer & operator=(const integer_t);

            virtual size_t serialize(OutputStream&) const;

            Integer & xch( Integer &) noexcept;



            const SignType s;
            const Natural  n;
        };
    }

    typedef Apex::Integer apz;

}

#endif

