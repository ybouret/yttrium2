#include "y/hashing/des64.hpp"
#include "y/hashing/ibj32.hpp"
#include "y/hashing/ibj64.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(hashing_mix64)
{
    Hashing::DES64 des64;
    Y_ASSERT(des64.test());

    Hashing::IBJ64 ibj64;

    for(unsigned i=0;i<10;++i)
    {
        std::cerr << Hexadecimal(i,Concise);
        std::cerr << " h32="   << Hexadecimal( Hashing::IBJ32(i) );
        std::cerr << " des64=" << Hexadecimal( des64.mix<unsigned,size_t>(i) );
        std::cerr << " ibj64=" << Hexadecimal( ibj64.mix<unsigned,size_t>(i) );

        std::cerr << std::endl;
    }

    


}
Y_UDONE()
