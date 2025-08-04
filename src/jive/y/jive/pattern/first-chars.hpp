
//! \file

#ifndef Y_Jive_FirstChars_Included
#define Y_Jive_FirstChars_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! FirstChars of pattern
        //
        //
        //______________________________________________________________________
        class FirstChars
        {
        public:

            //__________________________________________________________________
            //
            //
            //! Definitions
            //
            //__________________________________________________________________
            static const unsigned Count = 256;      //!< alias
            static const unsigned Bytes = Count/8;  //!< alias
            typedef void (*Proc)(const uint8_t, const uint8_t, void *); //!< alias

            //__________________________________________________________________
            //
            //
            //  C++
            //
            //__________________________________________________________________
            FirstChars() noexcept;                               //!< setup empty
            FirstChars(const FirstChars &) noexcept;             //!< duplicate
            FirstChars & operator=(const FirstChars &) noexcept; //!< assign \return *this
            Y_OSTREAM_PROTO(FirstChars);                         //!< display
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void free()                noexcept; //!< all off
            void all()                 noexcept; //!< all on
            void add(const uint8_t)    noexcept; //!< add single byte
            void add(uint8_t, uint8_t) noexcept; //!< add range
            void sub(const uint8_t)    noexcept; //!< remove single bute
            void sub(uint8_t, uint8_t) noexcept; //!< remove range

            FirstChars & operator +=(const FirstChars &) noexcept; //!< bitwise add \return *this
            FirstChars & operator -=(const FirstChars &) noexcept; //!< bitwise sub \return *this

            //! call procedure for all ranges/single
            void run(Proc, void * const) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t size;   //!< bit count
        private:
            uint8_t data[Bytes]; //!< bit fields
            bool getbit(const uint8_t) const noexcept; //!< \return get bit value
            void setbit(const uint8_t) noexcept;       //!< set bit to on
            void clrbit(const uint8_t) noexcept;       //!< clr bit to off

            unsigned findLowerBit(const unsigned) const noexcept;    //!< \return next on bit
            unsigned findUpperBit(const unsigned) const noexcept;    //!< \return still on bit
            static void Print(const uint8_t, const uint8_t, void *); //!< helper to display
        };
    }
}

#endif

