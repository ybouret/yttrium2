
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
            static OpsMode Ops; //!< operating mode

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Natural();                                     //!< setup zero
            virtual ~Natural() noexcept;                   //!< cleanup
            Natural(const Natural &);                      //!< duplicate
            Natural & operator=(const Natural &);          //!< assign \return *this*
            Natural(const natural_t);                      //!< setup to natural_t
            Natural & operator=(const natural_t) noexcept; //!< assign \return *this

            Natural(const TwoToThePowerOf_ &, const size_t n);  //!< \param n setup to 2^n
            Natural(InputStream &, const char * const);         //!< load save value
            Y_OSTREAM_PROTO(Natural);                           //!< display

            //! setup to random bits
            /**
             \param ran random bits
             \param numBits exact number of bits
             */
            Natural(Random::Bits &ran, const size_t numBits);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String    hexString()      const;         //!< \return hexadecimal string
            size_t    bits()  const noexcept;         //!< \return number of bits
            size_t    bytes() const noexcept;         //!< \return number of bytes
            void      relax()        noexcept;        //!< relax to Ops matching view
            void      alter(const ViewType) noexcept; //!< alter to given viea
            Natural & xch(Natural &) noexcept;        //!< exchange \return *this

            //__________________________________________________________________
            //
            //
            // comparison
            //
            //__________________________________________________________________
#if !DOXYGEN_SHOULD_SKIP_THIS
            Y_APN_Compare_Impl(==, == __Zero__)
            Y_APN_Compare_Impl(!=, != __Zero__)
            Y_APN_Compare_Impl(<,  == Negative)
            Y_APN_Compare_Impl(>  ,== Positive)
            Y_APN_Compare_Impl(<=, != Positive)
            Y_APN_Compare_Impl(>=, != Negative)

            Y_APN_Operator_Impl(+,Add)
            Y_APN_Operator_Impl(-,Sub)
#endif
            //__________________________________________________________________
            //
            //
            // Comparison
            //
            //__________________________________________________________________
            static SignType Compare(const Natural &, const Natural &);          //!< \return comparison
            static SignType Compare(const Natural &, const natural_t) noexcept; //!< \return comparison
            static SignType Compare(const natural_t, const Natural &) noexcept; //!< \return comparison

            //__________________________________________________________________
            //
            //
            // Addition
            //
            //__________________________________________________________________
            Natural   operator+() const; //!< \return duplicate
            Natural & operator++();      //!< prefix  \return increased *this
            Natural   operator++(int);   //!< postfix \return previous  *this, increased

            //__________________________________________________________________
            //
            //
            // Subtraction
            //
            //__________________________________________________________________
            Natural & operator--();      //!< prefix  \return decreased *this
            Natural   operator--(int);   //!< postfix \return previous  *this, decreased

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream &) const;


            
        private:
            Model * const code; //!< internal representation
            Natural(const Attach_ &, Model * const) noexcept; //!< setup directly



            Y_APN_Proto_Decl(static Model *,Add); //!< addition prototypes
            void incr();                          //!< increment

            Y_APN_Proto_Decl(static Model *,Sub); //!< subtraction prototypes
            void decr();
        };


    }

    typedef Apex::Natural apn;

}

#endif

