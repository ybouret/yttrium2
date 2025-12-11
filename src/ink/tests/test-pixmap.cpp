

#include "y/ink/pixmap.hpp"
#include "y/utest/run.hpp"

#if defined(_MSC_VER)
#pragma warning (disable:4464)
#endif
#include "../../core/tests/main.hpp"


namespace Yttrium
{
    namespace Ink
    {

        

    }
}

using namespace Yttrium;
using namespace Ink;

Y_UTEST(pixmap)
{
    Random::MT19937 ran;


    {
        Pixmap<String> p(5,8);
        for(unit_t j=0;j<=p.upper.y;++j)
        {
            Y_ASSERT(j==p.zflux[j]);
            for(unit_t i=0;i<=p.upper.x;++i)
            {
                assert(i==p[j].z[i]);
                const String s = Gen<String>::New(ran);
                std::cerr << " " << s;
                p[j][i] = s;
                Y_ASSERT( &p[j][i] == &p( (size_t)j)( (size_t)i) );
            }
            std::cerr << std::endl;
        }
        std::cerr << p << std::endl;
    }

    {
        Pixmap<int> p(8,5);
        for(size_t j=0;j<p.h;++j)
        {
            for(size_t i=0;i<p.w;++i)
            {
                p(j)(i) = Gen<int16_t>::New(ran);
            }
        }

        std::cerr << std::endl << p << std::endl;

        Pixmap<float> f(CopyOf,p);
        std::cerr << std::endl << f << std::endl;

    }



}
Y_UDONE()
