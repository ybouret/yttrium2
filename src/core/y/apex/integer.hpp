
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    
    namespace Apex
    {
#define Y_APZ_Proto_Decl(RET,FUNC) \
RET FUNC(const Integer &, const Integer &);\
RET FUNC(const integer_t, const Integer &);\
RET FUNC(const Integer &, const integer_t);\
RET FUNC(const Integer &, const Natural &);\
RET FUNC(const Natural &, const Integer &)


        //! helper to implement one comparison operator
#define Y_APZ_Compare_Impl_(OP,LHS,RHS,RES) \
inline friend bool operator OP(const LHS lhs, const RHS rhs) { return Compare(lhs,rhs) RES; }

        //! helper to implement multiple comparison operators
#define Y_APZ_Compare_Impl(OP,RES)              \
Y_APZ_Compare_Impl_(OP,Integer &,Integer &,RES) \
Y_APZ_Compare_Impl_(OP,integer_t,Integer &,RES) \
Y_APZ_Compare_Impl_(OP,Integer &,integer_t,RES) \
Y_APZ_Compare_Impl_(OP,Integer &,Natural &,RES) \
Y_APZ_Compare_Impl_(OP,Natural &,Integer &,RES) \

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

            Y_APZ_Proto_Decl(static SignType,Compare);
            Y_APZ_Proto_Decl(static Integer,Add);


#if !DOXYGEN_SHOULD_SKIP_THIS
            Y_APZ_Compare_Impl(==, == __Zero__)
            Y_APZ_Compare_Impl(!=, != __Zero__)
            Y_APZ_Compare_Impl(<,  == Negative)
            Y_APZ_Compare_Impl(>  ,== Positive)
            Y_APZ_Compare_Impl(<=, != Positive)
            Y_APZ_Compare_Impl(>=, != Negative)
#endif


            const SignType s;
            const Natural  n;

        private:
            Integer(const SignType, const Natural &);


        };
    }

    typedef Apex::Integer apz;

}

#endif

