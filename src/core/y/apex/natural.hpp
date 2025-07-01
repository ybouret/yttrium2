
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/types.hpp"
#include "y/apex/number.hpp"
#include "y/apex/block/ops.hpp"
#include "y/apex/block/view.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/ostream-proto.hpp"
#include "y/string.hpp"

namespace Yttrium
{

    namespace Random { class Bits; }

    namespace Apex
    {
        class Model;

#define Y_APN_Proto_Decl(RETURN,FUNC) \
RETURN FUNC(const Natural &, const Natural &);\
RETURN FUNC(const Natural &, const natural_t);\
RETURN FUNC(const natural_t, const Natural &)

#define Y_APN_Method_Decl(RETURN,FUNC,CALL) \
inline RETURN FUNC(const Natural & lhs, const Natural & rhs) { return CALL(lhs,rhs); } \
inline RETURN FUNC(const Natural & lhs, const natural_t rhs) { return CALL(lhs,rhs); } \
inline RETURN FUNC(const natural_t lhs, const Natural & rhs) { return CALL(lhs,rhs); }

#define Y_APN_Operator_Decl(OP,CALL) \
Y_APN_Method_Decl(friend Natural,operator OP,CALL)\
inline Natural & operator OP##=(const Natural & rhs) { Natural res( CALL(*this,rhs) ); return xch(res); }\
inline Natural & operator OP##=(const natural_t rhs) { Natural res( CALL(*this,rhs) ); return xch(res); }

#define Y_APN_Compare_Decl_(OP,LHS,RHS,RES) \
inline friend bool operator OP(const LHS lhs, const RHS rhs) { return Compare(lhs,rhs) RES; }

#define Y_APN_Compare_Decl(OP,RES)              \
Y_APN_Compare_Decl_(OP,Natural &,Natural &,RES) \
Y_APN_Compare_Decl_(OP,natural_t,Natural &,RES) \
Y_APN_Compare_Decl_(OP,Natural &,natural_t,RES)



        class Natural : public Number
        {
        public:
            // Definitions
            static OpsMode Ops;

            // C++
            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t) noexcept;

            Natural(const TwoToThePowerOf_ &, const size_t n);
            Natural(InputStream &, const char * const varName);
            Y_OSTREAM_PROTO(Natural);

            Natural(Random::Bits &ran, const size_t numBits);


            String hexString() const;
            size_t    bits()  const noexcept;
            size_t    bytes() const noexcept;
            void      relax()        noexcept;
            void      alter(const ViewType) noexcept;
            Natural & xch(Natural &) noexcept;

            // comparisons
            Y_APN_Compare_Decl(==, == __Zero__)
            Y_APN_Compare_Decl(!=, != __Zero__)
            Y_APN_Compare_Decl(<,  == Negative)
            Y_APN_Compare_Decl(>  ,== Positive)
            Y_APN_Compare_Decl(<=, != Positive)
            Y_APN_Compare_Decl(>=, != Negative)

            // addition
            Natural operator+() const; //!< \return duplicate
            Y_APN_Operator_Decl(+,Add)
            Natural & operator++();
            Natural   operator++(int);

            // interface
            virtual size_t serialize(OutputStream &fp) const;

            static SignType Compare(const Natural &, const Natural &);
            static SignType Compare(const Natural &, const natural_t) noexcept;
            static SignType Compare(const natural_t, const Natural &) noexcept;
            
        private:
            Model * const code;
            Natural(Model * const) noexcept;



            Y_APN_Proto_Decl(static Model *,Add); //!< addition prototypes
            void incr();                          //!< increment


        };


    }

}

#endif

