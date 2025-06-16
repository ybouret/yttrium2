
//! \file

#ifndef Y_Binary_Included
#define Y_Binary_Included 1

#include "y/ability/legacy-string.hpp"
#include "y/type/ints.hpp"
#include "y/core/display.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    class Binary : public LegacyString
    {
    public:
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

        virtual ~Binary() noexcept;
        Binary(const Binary &) noexcept;
        
        virtual const char * c_str() const noexcept;

    private:
        Y_Disable_Assign(Binary);
        const size_t count;
        char         array[64+sizeof(void*)];

        void ldz() noexcept;
    };
}

#endif

