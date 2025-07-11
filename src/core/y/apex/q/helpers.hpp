//! \file

#ifndef Y_Apex_Rational_Helpers_Included
#define Y_Apex_Rational_Helpers_Included 1

//! helper
#define Y_APQ_Proto_Decl(RET,FUNC)            \
RET FUNC(const Rational &, const Rational &); \
RET FUNC(const Rational &, const Integer  &); \
RET FUNC(const Integer  &, const Rational &); \
RET FUNC(const Rational &, const Natural  &); \
RET FUNC(const Natural  &, const Rational &); \
RET FUNC(const Rational &, const integer_t ); \
RET FUNC(const integer_t , const Rational &)

//! helper
#define Y_APQ_Compare_Proto(OP,LHS,RHS,RET) \
inline friend bool operator OP (const LHS lhs, const RHS rhs) noexcept { return Compare(lhs,rhs) RET; }


//! helper
#define Y_APQ_Compare_Decl(OP,RET) \
Y_APN_Compare_Proto(OP,Rational &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, Integer  &,RET) \
Y_APN_Compare_Proto(OP,Integer  &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, Natural  &,RET) \
Y_APN_Compare_Proto(OP,Natural  &, Rational &,RET) \
Y_APN_Compare_Proto(OP,Rational &, integer_t ,RET) \
Y_APN_Compare_Proto(OP,integer_t , Rational &,RET)


//! helper
#define Y_APQ_Operator_Proto_Binary(OP,LHS,RHS,CALL) \
inline friend Rational operator OP (const LHS lhs, const RHS rhs) { return CALL(lhs,rhs); }

//! helper
#define Y_APQ_Operator_Impl_Binary(OP,CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Integer &, CALL)  \
Y_APQ_Operator_Proto_Binary(OP, Integer  &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, Natural &, CALL)  \
Y_APQ_Operator_Proto_Binary(OP, Natural  &, Rational &, CALL) \
Y_APQ_Operator_Proto_Binary(OP, Rational &, integer_t,  CALL) \
Y_APQ_Operator_Proto_Binary(OP, integer_t,  Rational &, CALL)

//! helper
#define Y_APQ_Operator_Proto_Unary(OP,RHS,CALL) \
inline Rational & operator OP##=(const RHS rhs) { Rational res( CALL(*this,rhs) ); return xch(res); }


//! helper
#define Y_APQ_Operator_Impl_Unary(OP,CALL)       \
Y_APQ_Operator_Proto_Unary(OP, Rational &, CALL) \
Y_APQ_Operator_Proto_Unary(OP, Integer  &, CALL) \
Y_APQ_Operator_Proto_Unary(OP, integer_t,  CALL) \
Y_APQ_Operator_Proto_Unary(OP, Natural &,  CALL)

//! helper
#define   Y_APQ_Operator_Impl(OP,CALL) \
Y_APQ_Operator_Impl_Binary(OP,CALL)    \
Y_APQ_Operator_Impl_Unary(OP,CALL)


#endif

