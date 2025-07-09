
//! \file

#ifndef Y_Apex_Natural_Helpers_Included
#define Y_Apex_Natural_Helpers_Included 1

//! helper
#define Y_APN_Proto_Decl_NoExcept(RET,FUNC)          \
RET FUNC(const Natural &, const Natural &) noexcept; \
RET FUNC(const Natural &, const natural_t) noexcept; \
RET FUNC(const natural_t, const Natural &) noexcept

//! helper
#define Y_APN_Compare_Proto(OP,LHS,RHS,RET) \
inline friend bool operator OP (const LHS lhs, const RHS rhs) noexcept { return Compare(lhs,rhs) RET; }

//! helper
#define Y_APN_Compare_Decl(OP,RET) \
Y_APN_Compare_Proto(OP,Natural &,Natural &,RET) \
Y_APN_Compare_Proto(OP,Natural &,natural_t,RET) \
Y_APN_Compare_Proto(OP,natural_t,Natural &,RET)

//! helper
#define Y_APN_Proto_Decl(RET,FUNC)          \
RET FUNC(const Natural &, const Natural &); \
RET FUNC(const Natural &, const natural_t); \
RET FUNC(const natural_t, const Natural &)

//! helper
#define Y_APN_Operator_Proto_Binary(OP,LHS,RHS,CALL) \
inline friend Natural operator OP (const LHS lhs, const RHS rhs) { return Natural(Hook,CALL(lhs,rhs)); }

//! helper
#define Y_APN_Operator_Impl_Binary(OP,CALL) \
Y_APN_Operator_Proto_Binary(OP,Natural &,Natural &,CALL) \
Y_APN_Operator_Proto_Binary(OP,Natural &,natural_t,CALL) \
Y_APN_Operator_Proto_Binary(OP,natural_t,Natural &,CALL) \

//! helper
#define Y_APN_Operator_Proto_Unary(OP,RHS,CALL) \
inline Natural & operator OP##=(const RHS rhs) { Natural res(Hook,CALL(*this,rhs)); return xch(res); }

//! helper
#define Y_APN_Operator_Impl_Unary(OP,CALL) \
Y_APN_Operator_Proto_Unary(OP,Natural &,CALL)\
Y_APN_Operator_Proto_Unary(OP,natural_t,CALL)

//! helper
#define Y_APN_Operator_Impl(OP,CALL) \
Y_APN_Operator_Impl_Binary(OP,CALL)  \
Y_APN_Operator_Impl_Unary(OP,CALL)

//! helper
#define Y_APN_DivMod_Impl(OP,CALL) \
inline friend Natural operator OP (const Natural & lhs, const Natural & rhs) { return CALL(lhs,rhs); }                     \
inline friend Natural operator OP (const Natural & lhs, const natural_t rhs) { const Natural _(rhs); return CALL(lhs,_); } \
inline friend Natural operator OP (const natural_t lhs, const Natural & rhs) { const Natural _(lhs); return CALL(_,rhs); } \
inline Natural & operator OP##=(const Natural & rhs) { Natural                       res = CALL(*this,rhs); return xch(res); } \
inline Natural & operator OP##=(const natural_t rhs) { const Natural _(rhs); Natural res = CALL(*this,_);   return xch(res); } \

#endif

