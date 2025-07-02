
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


#define Y_APZ_Method_Impl(RETURN,FUNC,CALL) \
inline RETURN FUNC(const Integer & lhs, const Integer & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Integer & lhs, const integer_t rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const integer_t lhs, const Integer & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Integer & lhs, const Natural & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Natural & lhs, const Integer & rhs) { return CALL(lhs,rhs); }


#define Y_APZ_Operator_Impl(OP,CALL) \
Y_APZ_Method_Impl(friend Integer,operator OP,CALL)\
inline Integer & operator OP##=(const Integer & rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }\
inline Integer & operator OP##=(const integer_t rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }\
inline Integer & operator OP##=(const Natural & rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }

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

            // Interface
            virtual size_t serialize(OutputStream&) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;

            // Methods
            Integer & xch( Integer &) noexcept;

            Y_APZ_Proto_Decl(static SignType,Compare);
            Y_APZ_Proto_Decl(static Integer,Add);
            Y_APZ_Proto_Decl(static Integer,Sub);


#if !DOXYGEN_SHOULD_SKIP_THIS
            Y_APZ_Compare_Impl(==, == __Zero__)
            Y_APZ_Compare_Impl(!=, != __Zero__)
            Y_APZ_Compare_Impl(<,  == Negative)
            Y_APZ_Compare_Impl(>  ,== Positive)
            Y_APZ_Compare_Impl(<=, != Positive)
            Y_APZ_Compare_Impl(>=, != Negative)
            Y_APZ_Operator_Impl(+,Add)
            Y_APZ_Operator_Impl(-,Sub)
#endif
            //__________________________________________________________________
            //
            //
            // Addition
            //
            //__________________________________________________________________
            Integer   operator+() const; //!< \return duplicate
            Integer & operator++();      //!< prefix  \return increased *this
            Integer   operator++(int);   //!< postfix \return previous  *this, increased

            //__________________________________________________________________
            //
            //
            // Subtraction
            //
            //__________________________________________________________________
            Integer   operator-() const; //!< \return opposite
            Integer & operator--();      //!< prefix  \return decreased *this
            Integer   operator--(int);   //!< postfix \return previous  *this, decreased


            //__________________________________________________________________
            //
            //
            // Conversion
            //
            //__________________________________________________________________
            template <typename T> inline
            bool tryCast(T &value) const noexcept
            {
                static const IntToType< IsSigned<T>::Value > choice = {};
                return tryCast(value,choice);
            }

            const SignType s;
            const Natural  n;

        private:
            Integer(const SignType, const Natural &);
            void incr();
            void decr();

            //! unsigned
            template <typename T> inline
            bool tryCast(T &value, const IntToType<false> &) const noexcept
            {
                switch(s)
                {
                    case Negative: return false;
                    case __Zero__: value = 0; return false;
                    case Positive: break;
                }
                if( n.bits() > sizeof(T)*8 ) return false;
                value = T( n.ls64() );
                return true;
            }

            //! signed
            template <typename T> inline
            bool tryCast(T &value, const IntToType<true> &) const noexcept
            {
                if( n.bits() > sizeof(T)*8-1 ) return false;
                switch(s)
                {
                    case __Zero__: value =  0;           break;
                    case Positive: value =  T(n.ls64()); break;
                    case Negative: value = -T(n.ls64()); break;
                }
                return true;
            }


        };
    }

    typedef Apex::Integer apz;

}

#endif

