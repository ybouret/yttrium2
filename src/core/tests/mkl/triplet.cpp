

#include "y/mkl/triplet.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;
using namespace MKL;



Y_UTEST(mkl_triplet)
{

    Random::MT19937 ran;

    Triplet<float> x = { 0, 2, 1 };
    std::cerr << x << std::endl;
    x.sort();
    std::cerr << x << std::endl;

    Random:: Shuffle::Range(ran,x(),3);
    std::cerr << x << std::endl;
    Triplet<size_t> idx = { 1,2,3 };
    x.sort(idx);
    std::cerr << x   << std::endl;
    std::cerr << idx << std::endl;
}
Y_UDONE()
