#include "y/container/light-array.hpp"
#include "y/ortho/vector.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;

Y_UTEST(apex_ortho_vector)
{

    Random::MT19937 ran;

    for(size_t dims=1;dims<=4;++dims)
    {
        std::cerr << std::endl << "--- dims=" << dims << std::endl;
        Ortho::Vector vec(dims);
        CxxArray<int> arr(dims);
        for(size_t iter=0;iter<4;++iter)
        {
            for(size_t i=dims;i>0;--i)
                arr[i] = ran.in<int>(-4,4);
            std::cerr << arr << " => ";
            const  Ortho::Vector src(CopyOf,arr);
            std::cerr << src << std::endl;
            {
                const  Ortho::Vector cpy(src);
                Y_ASSERT(src==cpy);
            }
            {
                vec.ldz();
                vec = src;
                Y_ASSERT(vec==src);
            }
            {
                vec.ldz();
                vec.assign(arr);
                Y_ASSERT(vec==src);
            }

            {
                CxxArray<apq> q(CopyOf,arr);
                vec.ldz();
                vec.assign(q);
                Y_ASSERT(vec==src);
            }
        }

        

    }


}
Y_UDONE()



