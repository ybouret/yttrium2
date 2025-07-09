
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
            static const char __Zero__Mark = 0;
            static const char PositiveMark = 1;
            static const char NegativeMark = 2;
            static const char * const CallSign; //!< "apz"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Integer();
            virtual ~Integer() noexcept;
            Integer(const Integer&);
            Integer &operator=(const Integer&);
            Y_OSTREAM_PROTO(Integer);
            Integer(const integer_t);
            Integer & operator=(const integer_t) noexcept;
            Integer(const Natural &);
            Integer(const SignType,const Natural &);
            Integer(Random::Bits &, const size_t);


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ldz() noexcept;
            virtual void ld1() noexcept;
            virtual size_t serialize(OutputStream&) const;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________
            void      ldm1() noexcept;
            Integer & xch(Integer &) noexcept;
            String    str() const;
            Integer   abs() const;
            Integer & neg() noexcept;

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
            Integer   operator++(int);   //!< postfix \return previous value, increase *this*
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


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const SignType s;
            const Natural  n;

            
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

    typedef Apex::Integer apz;

}

#endif

