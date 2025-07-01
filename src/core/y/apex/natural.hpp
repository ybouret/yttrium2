
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
        Y_Shallow_Decl(Attach); //!< helper for constructor

        //! helper to declare multiple methods
#define Y_APN_Proto_Decl(RETURN,FUNC) \
RETURN FUNC(const Natural &, const Natural &);\
RETURN FUNC(const Natural &, const natural_t);\
RETURN FUNC(const natural_t, const Natural &)

        //! helper to implement multiple methods
#define Y_APN_Method_Impl(RETURN,FUNC,CALL) \
inline RETURN FUNC(const Natural & lhs, const Natural & rhs) { return Natural(Attach,CALL(lhs,rhs)); } \
inline RETURN FUNC(const Natural & lhs, const natural_t rhs) { return Natural(Attach,CALL(lhs,rhs)); } \
inline RETURN FUNC(const natural_t lhs, const Natural & rhs) { return Natural(Attach,CALL(lhs,rhs)); }

        //! helper to implement multiple operators
#define Y_APN_Operator_Impl(OP,CALL) \
Y_APN_Method_Impl(friend Natural,operator OP,CALL)\
inline Natural & operator OP##=(const Natural & rhs) { Natural res(Attach,CALL(*this,rhs) ); return xch(res); }\
inline Natural & operator OP##=(const natural_t rhs) { Natural res(Attach,CALL(*this,rhs) ); return xch(res); }

        //! helper to implement one comparison operator
#define Y_APN_Compare_Impl_(OP,LHS,RHS,RES) \
inline friend bool operator OP(const LHS lhs, const RHS rhs) { return Compare(lhs,rhs) RES; }

        //! helper to implement multiple comparison operators
#define Y_APN_Compare_Impl(OP,RES)              \
Y_APN_Compare_Impl_(OP,Natural &,Natural &,RES) \
Y_APN_Compare_Impl_(OP,natural_t,Natural &,RES) \
Y_APN_Compare_Impl_(OP,Natural &,natural_t,RES)


        //______________________________________________________________________
        //
        //
        //
        //! Natural number
        //
        //
        //______________________________________________________________________
        class Natural : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static OpsMode Ops;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
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
            Y_APN_Compare_Impl(==, == __Zero__)
            Y_APN_Compare_Impl(!=, != __Zero__)
            Y_APN_Compare_Impl(<,  == Negative)
            Y_APN_Compare_Impl(>  ,== Positive)
            Y_APN_Compare_Impl(<=, != Positive)
            Y_APN_Compare_Impl(>=, != Negative)

            // addition
            Natural operator+() const; //!< \return duplicate
            Y_APN_Operator_Impl(+,Add)
            Natural & operator++();
            Natural   operator++(int);

            // interface
            virtual size_t serialize(OutputStream &fp) const;

            static SignType Compare(const Natural &, const Natural &);
            static SignType Compare(const Natural &, const natural_t) noexcept;
            static SignType Compare(const natural_t, const Natural &) noexcept;
            
        private:
            Model * const code;
            Natural(const Attach_ &, Model * const) noexcept;



            Y_APN_Proto_Decl(static Model *,Add); //!< addition prototypes
            void incr();                          //!< increment


        };


    }

}

#endif

