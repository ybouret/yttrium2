#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/ops/filter/metrics.hpp"
#include "y/ink/ops/filter/sum.hpp"

#include "y/container/cxx/series.hpp"




namespace Yttrium
{
    namespace Ink
    {
        
        template <typename T>
        class Filter : public FilterMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            template <typename U>
            inline explicit Filter(const U   * const blockAddr,
                                   const size_t      blockSize) :
            FilterMetrics(blockSize),
            CxxSeries< FilterElement<T> >( Count(blockAddr,blockSize) ),
            sum(0)
            {
                size_t i=0;
                for(unit_t y=-delta;y<=delta;++y)
                {
                    for(unit_t x=-delta;x<=delta;++x)
                    {
                        const T W = blockAddr[i++];
                        switch( Sign::Of(W) )
                        {
                            case __Zero__: continue;
                            case Negative:
                            case Positive:
                                break;
                        }
                        const Point C(x,y);
                        this->push(C,W);
                    }
                }
                Coerce(sum) = FilterSum<T>::Compute( *this );
            }


            inline virtual ~Filter() noexcept {}

            const T sum;


        private:
            Y_Disable_Copy_And_Assign(Filter);
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

    Filter<float> F( &f[0][0], sizeof(f)/sizeof(f[0][0]));
    std::cerr << F << "/" << F.sum << std::endl;


    Filter<int> Fi( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fi<< "/" << Fi.sum << std::endl;

    Filter<uint32_t> Fu( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fu<< "/" << Fu.sum << std::endl;
}
Y_UDONE()
