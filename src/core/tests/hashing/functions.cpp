
#include "y/hashing/adler32.hpp"
#include "y/hashing/crc16.hpp"
#include "y/hashing/crc32.hpp"
#include "y/hashing/elf.hpp"
#include "y/hashing/fnv.hpp"
#include "y/hashing/md2.hpp"
#include "y/hashing/md4.hpp"
#include "y/hashing/md5.hpp"
#include "y/hashing/pjw.hpp"
#include "y/hashing/rmd128.hpp"
#include "y/hashing/rmd160.hpp"
#include "y/hashing/sfh.hpp"
#include "y/hashing/sha1.hpp"
#include "y/hashing/sha256.hpp"
#include "y/hashing/sha512.hpp"

#include "y/utest/run.hpp"

#include "y/hashing/md.hpp"


#include "y/container/associative/suffix/map.hpp"
#include "y/pointer/arc.hpp"
#include "y/string.hpp"

#include "y/stream/libc/input.hpp"

using namespace Yttrium;

typedef  ArcPtr<Hashing::Function>  HFuncPtr;
typedef  SuffixMap<String,HFuncPtr> HFuncMap;



#define HREG(F) do {\
const HFuncPtr p = new Hashing::F(); \
const String   k = p->callSign(); \
if( !hmap.insert(k,p) ) throw Exception("multiple '%s'", k.c_str() ); \
} while(false)
Y_UTEST(hashing_functions)
{
    HFuncMap hmap;

    HREG(Adler32);
    HREG(CRC16);
    HREG(CRC32);
    HREG(ELF);
    HREG(FNV);
    HREG(MD2);
    HREG(MD4);
    HREG(MD5);
    HREG(PJW);
    HREG(RMD128);
    HREG(RMD160);
    HREG(SFH);
    HREG(SHA1);
    HREG(SHA256);
    HREG(SHA224);
    HREG(SHA512);
    HREG(SHA384);

    Hashing::MD5::Tests();
    Hashing::RMD160::Tests();
    Hashing::SHA1::Tests();
    Hashing::SHA256::Tests();
    Hashing::SHA224::Tests();

    for(HFuncMap::Iterator it=hmap.begin();it!=hmap.end();++it)
    {
        (**it).set();
    }

    if( argc > 1 )
    {
        InputFile fp(argv[1]);
        char c = 0;
        while(fp.query(c))
        {
            for(HFuncMap::Iterator it=hmap.begin();it!=hmap.end();++it)
            {
                (**it).run(&c,1);
            }
        }
    }

    for(HFuncMap::Iterator it=hmap.begin();it!=hmap.end();++it)
    {
        Hashing::Function &   H = **it;
        const Hashing::Digest D = Hashing::MD::Of(H);
        std::cerr << std::setw(20) << H.callSign()  << " : " << D << std::endl;
    }

}
Y_UDONE()

