
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/apex/k/ops.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/ostream-proto.hpp"
#include "y/apex/k/plan.hpp"
#include "y/type/sign.hpp"
#include "y/apex/n/shielded.hpp"
#include "y/apex/n/smartdev.hpp"

namespace Yttrium
{
    namespace Random { class Bits; }

    namespace Apex
    {

        Y_Shallow_Decl(Hook);

#define Y_APN_Proto_Decl_NoExcept(RET,FUNC)          \
RET FUNC(const Natural &, const Natural &) noexcept; \
RET FUNC(const Natural &, const natural_t) noexcept; \
RET FUNC(const natural_t, const Natural &) noexcept

#define Y_APN_Compare_Proto(OP,LHS,RHS,RET) \
inline friend bool operator OP (const LHS lhs, const RHS rhs) noexcept { return Compare(lhs,rhs) RET; }

#define Y_APN_Compare_Decl(OP,RET) \
Y_APN_Compare_Proto(OP,Natural &,Natural &,RET) \
Y_APN_Compare_Proto(OP,Natural &,natural_t,RET) \
Y_APN_Compare_Proto(OP,natural_t,Natural &,RET)


#define Y_APN_Proto_Decl(RET,FUNC)          \
RET FUNC(const Natural &, const Natural &); \
RET FUNC(const Natural &, const natural_t); \
RET FUNC(const natural_t, const Natural &)

#define Y_APN_Operator_Proto_Binary(OP,LHS,RHS,CALL) \
inline friend Natural operator OP (const LHS lhs, const RHS rhs) { return Natural(Hook,CALL(lhs,rhs)); }

#define Y_APN_Operator_Impl_Binary(OP,CALL) \
Y_APN_Operator_Proto_Binary(OP,Natural &,Natural &,CALL) \
Y_APN_Operator_Proto_Binary(OP,Natural &,natural_t,CALL) \
Y_APN_Operator_Proto_Binary(OP,natural_t,Natural &,CALL) \


#define Y_APN_Operator_Proto_Unary(OP,RHS,CALL) \
inline Natural & operator OP##=(const RHS rhs) { Natural res(Hook,CALL(*this,rhs)); return xch(res); }

#define Y_APN_Operator_Impl_Unary(OP,CALL) \
Y_APN_Operator_Proto_Unary(OP,Natural &,CALL)\
Y_APN_Operator_Proto_Unary(OP,natural_t,CALL)


#define Y_APN_Operator_Impl(OP,CALL) \
Y_APN_Operator_Impl_Binary(OP,CALL)  \
Y_APN_Operator_Impl_Unary(OP,CALL)

       

        class Natural : public SmartDev, public Shielded
        {
        public:
            static OpsMode            Ops;      //!< for multiplication/division
            static PlanType           Cmp;      //!< for comparisons
            static PlanType           BWO;      //!< for BitWise Ops
            static const char * const CallSign; //!< "apn"

            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t);
            Y_OSTREAM_PROTO(Natural);

            Natural(Random::Bits & , const size_t);
            Natural(const TwoToThePowerOf_ &, const size_t );
            Natural(InputStream &, const char * const = 0 );

            virtual size_t serialize(OutputStream &) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;
            size_t         bits() const noexcept;
            Natural &      xch(Natural &) noexcept;
            uint64_t       ls64() const   noexcept;

            void alter(const PlanType) noexcept;

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
#endif

            Natural   operator+() const; //!< \return *this
            Natural & operator++();      //!< prefix  \return increased *this
            Natural   operator++(int);   //!< postfix \return previous value, increase *this*
            void      incr();

            Natural & operator--();      //!< prefix  \return decreased *this
            Natural   operator--(int);   //!< postfix \return previous value, decrease *this*
            void      decr();


            void    shr() noexcept; //!< in-place shr
            Natural abs() const;


        private:
            Natural(const Hook_ &, Device *);
        };
    }
    
    typedef Apex::Natural apn;
}

#endif
