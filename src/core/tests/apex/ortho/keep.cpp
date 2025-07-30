
#include "y/container/light-array.hpp"
#include "y/ortho/vector.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/ascii/boolean.hpp"

using namespace Yttrium;

Y_UTEST(apex_ortho_keep)
{

    Random::MT19937 ran;

    for(size_t dims=1;dims<=4;++dims)
    {
        std::cerr << std::endl << "--- dims=" << dims << std::endl;
        CxxArray<int>       arr(dims);
        for(size_t iter=0;iter<4;++iter)
        {
            for(size_t i=dims;i>0;--i)
                arr[i] = ran.in<int>(-4,4);
            std::cerr << arr << " => ";
            const Ortho::Vector b(CopyOf,arr);
            std::cerr << b << std::endl;


            for(size_t jter=0;jter<4;++jter)
            {
                for(size_t i=dims;i>0;--i)
                    arr[i] = ran.in<int>(-10,10);
                Ortho::Vector a(CopyOf,arr);
                std::cerr <<  "\ta=" << a << " => ";
                const bool keep = a.keepOrtho(b);
                std::cerr << ASCII::Boolean::Text(keep) << " aa=" << a << std::endl;
            }

        }

    }


}
Y_UDONE()



