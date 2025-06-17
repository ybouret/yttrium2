
#include "y/information/stream/arc4.hpp"

#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/memory/buffer/out-of.hpp"
#include "y/object/factory.hpp"
#include "y/hexadecimal.hpp"
#include <cstring>
#include "y/memory/allocator/pooled.hpp"
#include "y/hexadecimal.hpp"

using namespace Yttrium;

namespace
{
    static inline void testArc4(const char * const Key,
                                const char * const Plain,
                                const char * const Cipher)
    {
        Y_ASSERT(Key);
        Y_ASSERT(Plain);
        Y_ASSERT(Cipher);

        Information::ARC4::Encoder enc(Key);

        const size_t length = strlen(Plain); Y_ASSERT(2*length==strlen(Cipher));
        Memory::BufferOutOf<Memory::Pooled> buffer(length);
        uint8_t * const Encoded = (uint8_t *)buffer.rw();
        enc.transform(Encoded,Plain,length);
        //Hexadecimal:: Display(std::cerr << "Encoded=",Encoded, length) << std::endl;

        for(size_t i=0,j=0;i<length;++i)
        {
            const uint8_t result = Encoded[i];
            uint8_t       target = uint8_t(Hexadecimal::ToDec(Cipher[j++]));
            (target <<= 4)      |= uint8_t(Hexadecimal::ToDec(Cipher[j++]));
            Y_ASSERT(result==target);
        }


    }
}

Y_UTEST(info_arc4)
{
    testArc4("Key",    "Plaintext",      "BBF316E8D940AF0AD3");
    testArc4("Wiki",   "pedia",          "1021BF0420");
    testArc4("Secret", "Attack at dawn", "45A01F645FC35B383552544B9BF5");
}
Y_UDONE()

