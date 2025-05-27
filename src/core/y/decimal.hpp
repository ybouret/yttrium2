//! \file

#ifndef Y_Decimal_Included
#define Y_Decimal_Included 1

#include "y/ability/legacy-string.hpp"
#include "y/ascii/cases.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/ints.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Decimal to legacy string conversion
    //
    //
    //__________________________________________________________________________
    class Decimal : public LegacyString
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        // uint64_t max = 18 446 744 073 709 551 615 : 20 chars, plus sign
        //
        //______________________________________________________________________
        static const unsigned MaxOutputSize = 20+1;                                           //!< to hold format
        static const unsigned RequiredChars = MaxOutputSize+1;                                //!< with terminal '\0'
        static const unsigned InternalChars = Alignment::On<4>::CeilOf<RequiredChars>::Value; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! initialize
        /**
         \param value any integral value
         */
        template <typename T> inline
        Decimal(const T &value) :
        LegacyString(),
        array()
        {
            static const IntToType< IsSigned<T>::Value > Choice = {};
            format(value,Choice);
        }

        Decimal(const Decimal &) noexcept; //!< duplicate
        virtual ~Decimal()       noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * c_str() const noexcept;

    private:
        Y_Disable_Assign(Decimal); //!< discarding
        char array[InternalChars]; //!< formatted
        void clear() noexcept;     //!< clear array
        void ldz()   noexcept;     //!< set "0" into array

        void uFormat(const uint64_t) noexcept; //!< format unsigned
        void sFormat(const int64_t)  noexcept; //!< format signed

        //! specialized format for unsigned
        /**
         \param value unsigned integral
         */
        template <typename T> inline
        void format( const T &value, const IntToType<false> &) noexcept {
            uFormat(value);
        }

        //! specialized format for signed
        /**
         \param value signed integral
         */
        template <typename T> inline
        void format( const T &value, const IntToType<true> &) noexcept {
            sFormat(value);
        }

    };
}


#endif

