#include "y/hashing/key/mixer.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(hashing_kmix)
{
    Hashing::KeyMixer kmix;

    int a = 1;           Y_PRINTV(kmix(a));
    a     = 2;           Y_PRINTV(kmix(a));
    const int b = 1;     Y_PRINTV(kmix(b));
    void * p = &a;       Y_PRINTV(kmix(p));
    const void * q = &a; Y_PRINTV(kmix(q));
}
Y_UDONE()
