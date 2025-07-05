
//! \file

#ifndef Y_Binary_Included
#define Y_Binary_Included 1

#include "y/ability/legacy-string.hpp"
#include "y/type/ints.hpp"
#include "y/core/display.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Binary to string representation
    //
    //
    //__________________________________________________________________________
    class Binary : public LegacyString
    {
    public:
        //! setup \param x integral value setting the bit count
        template <typename T>
        inline Binary(const T &x) noexcept :
        LegacyString(),
        count(sizeof(T)*8),
        array()
        {
            ldz();
            typedef typename UnsignedIntFor<T>::Result::Type U;
            const union {
                T data;
                U word;
            } alias = { x };

            const U one(1);
            U       bit = one<<(count-1);
            const U inf = alias.word;

            for(size_t i=0;i<count;++i,bit>>=1)
            {
                if(0!=(inf&bit)) array[i] = '1'; else array[i] = '0';
            }
        }

        virtual ~Binary() noexcept;      //!< cleanup
        Binary(const Binary &) noexcept; //!< duplicate

        virtual const char * c_str() const noexcept;

    private:
        Y_Disable_Assign(Binary); //!< discarding
        void ldz() noexcept;      //!< clear array

        const size_t count;                   //!< bit count
        char         array[64+sizeof(void*)]; //!< encoded string

    };
}

#endif

