
#include "y/information/stream/delta.hpp"
#include "y/information/stream/move-to-front.hpp"
#include "y/information/stream/arc4.hpp"

#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/memory/buffer/out-of.hpp"
#include "y/object/factory.hpp"
#include "y/hexadecimal.hpp"
#include "y/system/rand.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    static inline
    void runCipher(Information::StreamCipher &sc, char *target, const char *source, const size_t length) noexcept
    {
        sc.restart();
        sc.transform(target,source,length);
    }

    static inline
    void runCodec(const char * const         uid,
                  Information::StreamCipher &enc,
                  Information::StreamCipher &dec,
                  const char * const         source)
    {
        Y_ASSERT(0!=uid);
        Y_ASSERT(0!=source);

        std::cerr << std::endl;
        std::cerr << "[" << uid << "]" << std::endl;
        const size_t       length = strlen(source);

        Hexadecimal::Display(std::cerr << "source  = ",source,length) << std::endl;
        Memory::BufferOutOf<Object::Factory> ebuffer(length);
        char * const       encoded = (char *) ebuffer.rw();
        runCipher(enc,encoded,source,length);
        Hexadecimal::Display(std::cerr << "encoded = ",encoded,length) << std::endl;

        Memory::BufferOutOf<Object::Factory> dbuffer(length);
        char * const       decoded = (char *) dbuffer.rw();
        runCipher(dec,decoded,encoded,length);
        Hexadecimal::Display(std::cerr << "decoded = ",decoded,length) << std::endl;
        Y_CHECK( 0 == memcmp(source,decoded,length) );
    }

}

Y_UTEST(info_stream)
{
    System::Rand ran;

    Information::Delta::Encoder deltaEnc;
    Information::Delta::Decoder deltaDec;

    Information::MoveToFront::Encoder mtfEnc;
    Information::MoveToFront::Decoder mtfDec;

    char buffer[256];
    const size_t length = ran.in(255);
    ran.fill(buffer,length);
    Information::ARC4::Encoder arc4Enc(buffer,length);
    Information::ARC4::Decoder arc4Dec(buffer,length);

    for(int i=1;i<argc;++i)
    {
        runCodec("Delta", deltaEnc, deltaDec, argv[i]);
        runCodec("MTF",   mtfEnc,   mtfDec,   argv[i]);
        runCodec("Arc4",  arc4Enc,  arc4Dec,  argv[i]);

    }
}
Y_UDONE()
