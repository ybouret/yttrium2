
#include "y/decimal.hpp"
#include "y/type/sign.hpp"
#include <cstring>


namespace Yttrium
{

    void Decimal:: clear() noexcept
    {
        memset(array,0,sizeof(array));
    }

    Decimal:: ~Decimal() noexcept
    {
        clear();
    }

    Decimal:: Decimal(const Decimal &_) noexcept :
    LegacyString(),
    array()
    {
        memcpy(array,_.array,sizeof(array));
    }

    const char *Decimal:: c_str() const noexcept
    {
        return array;
    }


    void Decimal:: ldz() noexcept
    {
        array[0] = '0';
    }

    static inline
    void format64(char *target, uint64_t x) noexcept
    {
        assert(0!=target);
        assert(x>0);
        const uint64_t ten = 10;
        char           tmp[32];
        size_t         nch = 0;
        memset(tmp,0,sizeof(tmp));

    SPLIT:
        const uint64_t q = x/ten;
        tmp[nch++] = '0'+int(x%ten);
        if(q>0)
        {
            x=q;
            goto SPLIT;
        }

        const char *source = tmp + nch;
        while(nch-- > 0)
        {
            *(target++) = *(--source);
        }




    }


    void Decimal:: uFormat(const uint64_t q) noexcept
    {
        clear();
        if(q<=0)
            ldz();
        else
        {
            format64(array,q);
        }
    }

    void Decimal:: sFormat(const int64_t q) noexcept
    {
        clear();
        switch( Sign::Of(q) )
        {
            case Positive: format64(array,q); return;
            case __Zero__: ldz(); return;
            case Negative: array[0] = '-'; format64(array+1,-q); return;
        }
    }

}
