
#include "y/hashing/hmac.hpp"
#include <cstring>

#if 0
namespace Yttrium
{
    namespace Hashing
    {
        const char HashMAC:: Prefix[] = "HMAC_";

        HashMAC:: ~HashMAC() noexcept
        {
            Coerce(L) = 0;
            Coerce(B) = 0;
        }


#define Y_HMAC_CTOR() \
L(H.length),          \
B(H.window),          \
key(B),               \
ikp(B),               \
okp(B),               \
tmp(L)

        HashMAC:: HashMAC(Function       &H,
                          const void     *key_addr,
                          const size_t    key_size) :
        Y_HMAC_CTOR()
        {
            assert(!(NULL==key_addr&&key_size>0));
            setup(H,key_addr,key_size);
        }


        HashMAC:: HashMAC(Function &H, const Memory::ReadOnlyBuffer &usr) :
        Y_HMAC_CTOR()
        {
            setup(H,usr.ro_addr(),usr.measure());
        }

        void HashMAC:: setup(Function    &H,
                             const void  *key_addr,
                             const size_t key_size) noexcept
        {
            assert(!(NULL==key_addr&&key_size>0));
            Coerce(key).ldz();
            if(key_size>B)
            {
                H.set();
                H.run(key_addr,key_size);
                H.get(Coerce(key)(),L);
            }
            else
            {
                memcpy(Coerce(key)(), key_addr, key_size);
            }

            for(size_t i=B;i>0;--i)
            {
                Coerce(ikp[i]) = uint8_t(key[i] ^ 0x36);
                Coerce(okp[i]) = uint8_t(key[i] ^ 0x5c);
            }

        }

        void HashMAC:: set(Function &H) noexcept
        {
            H.set();
            H(ikp);
        }

        const Memory::ReadOnlyBuffer  & HashMAC:: get(Function &H) noexcept
        {
            H.get(tmp(),L);
            H.set();
            H(okp);
            H(tmp);
            H.get(tmp(),L);
            return tmp;
        }

    }

}


#endif

