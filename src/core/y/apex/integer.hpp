
//! \file

#ifndef Y_Apex_Integer_Included
#define Y_Apex_Integer_Included 1

#include "y/apex/natural.hpp"
#include "y/apex/z/helpers.hpp"

namespace Yttrium
{

    namespace Apex
    {

        
        //______________________________________________________________________
        //
        //
        //
        //! Integer number
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
            static const char __Zero__Mark = 0; //!< to serialize zero
            static const char PositiveMark = 1; //!< to serialize positive
            static const char NegativeMark = 2; //!< to serialize negstive
            static const char * const CallSign; //!< "apz"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Integer();                                     //!< setup
            virtual ~Integer() noexcept;                   //!< cleanup
            Integer(const Integer&);                       //!< duplicate
            Integer &operator=(const Integer&);            //!< assign \return *this
            Y_OSTREAM_PROTO(Integer);                      //!< display
            Integer(const integer_t);                      //!< setup from integral
            Integer & operator=(const integer_t) noexcept; //!< assign integral \return *this*
            Integer(const Natural &);                      //!< setup from Natural
            Integer(const SignType,const Natural &);       //!< setup from sign + natura
            Integer(Random::Bits &, const size_t);         //!< setup with random bits and sign
            Integer & operator=(const Natural &);          //!< assign integral \return *this
            Integer(InputStream &, const char * const=0);  //!< reload from saved state


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t       serialize(OutputStream &) const;
            virtual const char * callSign()       const noexcept;
            virtual void         ldz()                  noexcept;
            virtual void         ld1()                  noexcept;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________
            void      ldm1()         noexcept; //!< no-throw set to -1
            Integer & xch(Integer &) noexcept; //!< no-throw exchange \return *this
            String    str()             const; //!< \return decimal string
            Integer   abs()             const; //!< \return |*this|
            Integer & neg()          noexcept; //!< in-place opposite \return *this*
            Integer   sqrt()             const; //!< \return (*this)^(1/2)
            void      shr()           noexcept; //!< divide by 2
            
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_APZ_Proto_Decl_NoExcept(static SignType,Compare);
            Y_APZ_Compare_Decl(==, == __Zero__)
            Y_APZ_Compare_Decl(!=, != __Zero__)
            Y_APZ_Compare_Decl(<,  == Negative)
            Y_APZ_Compare_Decl(>,  == Positive)
            Y_APZ_Compare_Decl(<=, != Positive)
            Y_APZ_Compare_Decl(>=, != Negative)

            Y_APZ_Proto_Decl(static Integer,Add);
            Y_APZ_Proto_Decl(static Integer,Sub);
            Y_APZ_Proto_Decl(static Integer,Mul);
            Y_APZ_Proto_Decl(static Integer,Div);

            Y_APZ_Operator_Impl(+,Add)
            Y_APZ_Operator_Impl(-,Sub)
            Y_APZ_Operator_Impl(*,Mul)
#endif

            //__________________________________________________________________
            //
            //
            // Specific additions
            //
            //__________________________________________________________________
            Integer   operator+() const; //!< \return *this
            Integer & operator++();      //!< prefix  \return increased *this
            Integer   operator++(int);   //!< postfix \return previous value, increase *this
            void      incr();            //!< in-place increase

            //__________________________________________________________________
            //
            //
            // Specific subtraction
            //
            //__________________________________________________________________
            Integer   operator-() const; //!< \return - *this
            Integer & operator--();      //!< prefix  \return decreased *this
            Integer   operator--(int);   //!< postfix \return previous value, decrease *this*
            void      decr();            //!< in-place decrease

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

            //! cast \param varName optional variable name \return casted when possible
            template <typename T> inline
            T cast(const char * const varName = 0) const
            {
                T res(0);
                if(!tryCast(res)) castOverflow(varName);
                return res;
            }
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const SignType s; //!< sign
            const Natural  n; //!< natural part

            
        private:
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

