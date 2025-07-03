
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{

    namespace Apex
    {


        //! helper to declare functions
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

        //! helper for method implementation
#define Y_APZ_Method_Impl(RETURN,FUNC,CALL) \
inline RETURN FUNC(const Integer & lhs, const Integer & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Integer & lhs, const integer_t rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const integer_t lhs, const Integer & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Integer & lhs, const Natural & rhs) { return CALL(lhs,rhs); }\
inline RETURN FUNC(const Natural & lhs, const Integer & rhs) { return CALL(lhs,rhs); }

        //! helper for operators implementations
#define Y_APZ_Operator_Impl(OP,CALL) \
Y_APZ_Method_Impl(friend Integer,operator OP,CALL)\
inline Integer & operator OP##=(const Integer & rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }\
inline Integer & operator OP##=(const integer_t rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }\
inline Integer & operator OP##=(const Natural & rhs) { Integer res( CALL(*this,rhs) ); return xch(res); }

        //______________________________________________________________________
        //
        //
        //
        //! Integer = signed natural
        //
        //
        //______________________________________________________________________
        class Integer : public Number
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char         Mark__Zero__ = 0x0; //!< marker for zero
            static const char         MarkPositive = 0x1; //!< marker for positive
            static const char         MarkNegative = 0x2; //!< marker for negative
            static const char * const CallSign;


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Integer();                                     //!< setup zero
            virtual ~Integer() noexcept;                   //!< cleanup
            Integer(const Integer &);                      //!< duplicate
            Integer & operator=(const Integer &);          //!< assign \return *this
            Y_OSTREAM_PROTO(Integer);                      //!< display
            Integer(const Natural &);                      //!< setup from natural
            Integer(const integer_t);                      //!< setup from integral
            Integer & operator=(const integer_t) noexcept; //!< assign from integral \return *this*

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream&) const;
            virtual void   ldz() noexcept;
            virtual void   ld1() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Integer & xch( Integer &) noexcept; //!< noexcept exchange \return *this*



#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_APZ_Proto_Decl(static SignType,Compare);
            Y_APZ_Proto_Decl(static Integer,Add);
            Y_APZ_Proto_Decl(static Integer,Sub);
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
            void      incr();           //!< in-place increase

            //__________________________________________________________________
            //
            //
            // Subtraction
            //
            //__________________________________________________________________
            Integer   operator-() const; //!< \return opposite
            Integer & operator--();      //!< prefix  \return decreased *this
            Integer   operator--(int);   //!< postfix \return previous  *this, decreased
            void      decr();            //!< in place decrease


            //__________________________________________________________________
            //
            //
            // Conversion
            //
            //__________________________________________________________________

            //! try cast
            /**
             \param value target
             \return true if possible
             */
            template <typename T> inline
            bool tryCast(T &value) const noexcept
            {
                static const IntToType< IsSigned<T>::Value > choice = {};
                return tryCast(value,choice);
            }

            //__________________________________________________________________
            //
            //
            // other
            //
            //__________________________________________________________________
            Integer abs() const; //!< \return |*this|

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const SignType s; //!< sign
            const Natural  n; //!< natural part

        private:
            Integer(const SignType, const Natural &); //!< manual setyp


            //! unsigned cast \param value target \return true if possible
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

            //! signed cast \param value target \return true if possible
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

    typedef Apex::Integer apz; //!< alias

}

#endif

