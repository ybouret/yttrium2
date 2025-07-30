
#include "y/hashing/adler32.hpp"
#include "y/hashing/md5.hpp"
#include "y/utest/run.hpp"

#include "y/container/associative/suffix/map.hpp"
#include "y/pointer/arc.hpp"
#include "y/string.hpp"

using namespace Yttrium;

typedef  ArcPtr<Hashing::Function>  HFuncPtr;
typedef  SuffixMap<String,HFuncPtr> HFuncMap;

Y_UTEST(hashing_functions)
{



    Hashing::MD5::Tests();
    

}
Y_UDONE()

