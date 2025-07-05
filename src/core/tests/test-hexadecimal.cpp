#include "y/format/hexadecimal.hpp"
#include "y/utest/run.hpp"
#include <cstdio>

using namespace Yttrium;

Y_UTEST(hexadecimal)
{

    std::cerr << Hexadecimal() << std::endl;

    {
        uint8_t x = 0xab;
        std::cerr << Hexadecimal(x) << std::endl;
    }

    {
        uint16_t x = 0xabcd;
        std::cerr << Hexadecimal(x) << std::endl;
    }

    {
        uint32_t x = 0x1234abcd;
        std::cerr << Hexadecimal(x) << std::endl;
    }

    {
        uint64_t x = 0x1234abcd5678efabULL;;
        std::cerr << Hexadecimal(x) << std::endl;
    }

    {
        int i = 3;
        std::cerr << Hexadecimal(i,Concise) << std::endl;
    }

    {
        unsigned short i = 0;
        std::cerr << Hexadecimal(i,Concise) << std::endl;
    }


#if 0
    fflush(stdout);
    {
        uint8_t k =0;
        for(size_t i=0;i<16;++i)
        {
            for(size_t j=0;j<16;++j,++k)
            {
                printf("\"%02x\", ", k);
            }
            printf("\n");
        }
        printf("\n");
    }

    {
        uint8_t k =0;
        for(size_t i=0;i<16;++i)
        {
            for(size_t j=0;j<16;++j,++k)
            {
                printf("\"%02X\", ", k);
            }
            printf("\n");
        }
        printf("\n");
    }
#endif

}
Y_UDONE()

