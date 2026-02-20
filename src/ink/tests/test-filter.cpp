#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/filter.hpp"





namespace Yttrium
{
    namespace Ink
    {

       

        template <typename SCALAR>
        struct ApplyFilter
        {
            template <typename T> static inline
            void Fill(T                    & target,
                      Filter<T>            & filter,
                      const Pixmap<SCALAR> & source,
                      const Point            point)
            {
                filter.template loadImmediate<SCALAR,SCALAR,1>(&target,source,point);
            }
        };


    }

}

using namespace Yttrium;
using namespace Ink;

Y_UTEST(filter)
{
    static const int8_t f[3][3] =
    {
        { 1, 2, 3 },
        { 4, 5 ,6 },
        { 7, 8, 9 }
    };

    Filter<float> F( &f[0][0], sizeof(f)/sizeof(f[0][0]), 4);
    std::cerr << F << std::endl;

    Pixmap<uint8_t> pxm(200,100);

    float target = 0;
    ApplyFilter<uint8_t>::Fill(target,F,pxm,Point(0,0));

}
Y_UDONE()
