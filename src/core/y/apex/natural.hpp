
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/types.hpp"
#include "y/apex/number.hpp"
#include "y/apex/block/ops.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/ostream-proto.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Model;

#define Y_APN_Proto_Decl(RETURN,FUNC) \
RETURN FUNC(const Natural &, const Natural &);\
RETURN FUNC(const Natural &, const natural_t);\
RETURN FUNC(const natural_t, const Natural &)

#define Y_APN_Method_Decl(RETURN,FUNC,CALL) \
RETURN FUNC(const Natural &lhs, const Natural &rhs) { return CALL(lhs,rhs); }

#define Y_APN_Operator_Decl(OP,CALL) \
Y_APN_Method_Decl(friend Natural,operator OP,CALL)\
Natural & operator OP##=(const Natural & rhs) { Natural res( CALL(*this,rhs) ); return xch(res); }\
Natural & operator OP##=(const natural_t rhs) { Natural res( CALL(*this,rhs) ); return xch(res); }


        class Natural : public Number
        {
        public:
            static OpsMode Ops;
            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t) noexcept;

            Natural(const TwoToThePowerOf_ &, const size_t n);
            Natural(InputStream &, const char * const varName);
            Y_OSTREAM_PROTO(Natural);

            String hexString() const;
            

            Natural & xch(Natural &) noexcept;


            // addition
            Natural operator+() const; //!< \return duplicate
            Y_APN_Operator_Decl(+,Add)
            Natural & operator++();
            Natural   operator++(int);

            // interface
            virtual size_t serialize(OutputStream &fp) const;
            
        private:
            Model * const code;
            Natural(Model * const) noexcept;

            Y_APN_Proto_Decl(static Model *,Add);
            void incr();
            
        };


    }

}

#endif

