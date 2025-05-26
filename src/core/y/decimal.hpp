//! \file

#ifndef Y_Decimal_Included
#define Y_Decimal_Included 1

#include "y/ability/legacy-string.hpp"
#include "y/ascii/cases.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/ints.hpp"


namespace Yttrium
{
    class Decimal : public LegacyString
    {
    public:
        // uint64_t max = 18 446 744 073 709 551 615 : 20 chars, plus sign
        static const unsigned MaxOutputSize = 21;
        static const unsigned RequiredChars = MaxOutputSize+1;
        static const unsigned InternalChars = Alignment::On<4>::CeilOf<RequiredChars>::Value; //!< alias

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

        virtual const char * c_str() const noexcept;

    private:
        Y_Disable_Assign(Decimal);
        char array[InternalChars];
        void clear() noexcept;
        void ldz()   noexcept; //!< "0"

        void uFormat(const uint64_t q) noexcept;
        void sFormat(const int64_t  q) noexcept;

        template <typename T> inline
        void format( const T &value, const IntToType<false> &) noexcept {
            uFormat(value);
        }

        template <typename T> inline
        void format( const T &value, const IntToType<true> &) noexcept {
            sFormat(value);
        }

    };
}


#endif

