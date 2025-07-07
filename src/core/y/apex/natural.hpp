
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
#include "y/apex/m/seal.hpp"

namespace Yttrium
{
    namespace Random { class Bits; }

    namespace Apex
    {


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



        class Device;

        class Natural : public Number
        {
        public:
            static OpsMode  Ops;
            static PlanType Cmp;
            
            static const char * const CallSign;

            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t);
            Y_OSTREAM_PROTO(Natural);

            Natural(Random::Bits &ran, const size_t bits);
            Natural(const TwoToThePowerOf_ &, const size_t n);


            virtual size_t serialize(OutputStream &) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;
            size_t         bits() const noexcept;
            Natural &      xch(Natural &) noexcept;
            uint64_t       ls64() const   noexcept;

            void alter(const PlanType) noexcept;

            Y_APN_Proto_Decl_NoExcept(static SignType,Compare);
            Y_APN_Compare_Decl(==, == __Zero__)
            Y_APN_Compare_Decl(!=, != __Zero__)
            Y_APN_Compare_Decl(<,  == Negative)
            Y_APN_Compare_Decl(>,  == Positive)
            Y_APN_Compare_Decl(<=, != Positive)
            Y_APN_Compare_Decl(>=, != Negative)


        private:
            mutable  Seal  seal;
            Device * const device;

        };

    }

    typedef Apex::Natural apn;
}

#endif
