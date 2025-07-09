

//! \file

#ifndef Y_Apex_Integer_Helpers_Included
#define Y_Apex_Integr_Helpers_Included 1



//! helper
#define Y_APZ_Proto_Decl_NoExcept(RET,FUNC)          \
RET FUNC(const Integer &, const Integer &) noexcept; \
RET FUNC(const Integer &, const integer_t) noexcept; \
RET FUNC(const integer_t, const Integer &) noexcept; \
RET FUNC(const Integer &, const Natural &) noexcept; \
RET FUNC(const Natural &, const Integer &) noexcept

//! helper
#define Y_APZ_Compare_Proto(OP,LHS,RHS,RET) \
inline friend bool operator OP (const LHS lhs, const RHS rhs) noexcept { return Compare(lhs,rhs) RET; }


//! helper
#define Y_APZ_Compare_Decl(OP,RET) \
Y_APN_Compare_Proto(OP,Integer &,Integer &,RET) \
Y_APN_Compare_Proto(OP,Integer &,integer_t,RET) \
Y_APN_Compare_Proto(OP,integer_t,Integer &,RET) \
Y_APN_Compare_Proto(OP,Integer &,Natural &,RET) \
Y_APN_Compare_Proto(OP,Natural &,Integer &,RET)

//! helper
#define Y_APZ_Proto_Decl(RET,FUNC)          \
RET FUNC(const Integer &, const Integer &); \
RET FUNC(const Integer &, const integer_t); \
RET FUNC(const integer_t, const Integer &); \
RET FUNC(const Integer &, const Natural &); \
RET FUNC(const Natural &, const Integer &)

//! helper
#define Y_APZ_Operator_Proto_Binary(OP,LHS,RHS,CALL) \
inline friend Integer operator OP (const LHS lhs, const RHS rhs) { return CALL(lhs,rhs); }

//! helper
#define Y_APZ_Operator_Impl_Binary(OP,CALL) \
Y_APZ_Operator_Proto_Binary(OP,Integer &,Integer &,CALL) \
Y_APZ_Operator_Proto_Binary(OP,Integer &,integer_t,CALL) \
Y_APZ_Operator_Proto_Binary(OP,integer_t,Integer &,CALL) \


//! helper
#define Y_APZ_Operator_Proto_Unary(OP,RHS,CALL) \
inline Integer & operator OP##=(const RHS rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }


//! helper
#define Y_APZ_Operator_Impl_Unary(OP,CALL)    \
Y_APZ_Operator_Proto_Unary(OP,Integer &,CALL) \
Y_APZ_Operator_Proto_Unary(OP,integer_t,CALL) \
Y_APZ_Operator_Proto_Unary(OP,Natural &,CALL)



//! helper
#define Y_APZ_Operator_Impl(OP,CALL) \
Y_APZ_Operator_Impl_Binary(OP,CALL)  \
Y_APZ_Operator_Impl_Unary(OP,CALL)

#endif

