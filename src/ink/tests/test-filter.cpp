#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/ops/filter/metrics.hpp"
#include "y/ink/ops/filter/sum.hpp"

#include "y/container/cxx/series.hpp"

#include "y/cameo/caddy.hpp"



namespace Yttrium
{
    namespace Ink
    {
        
        template <typename T>
        class Filter : public FilterMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            typedef Cameo::Addition<T> Addition;
            typedef Cameo::Caddy<T>    Additions;

            template <typename U>
            inline explicit Filter(const U   * const blockAddr,
                                   const size_t      blockSize) :
            FilterMetrics(blockSize),
            CxxSeries< FilterElement<T> >( Count(blockAddr,blockSize) ),
            adds(),
            wsum(0)
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
                Coerce(wsum) = FilterSum<T>::Compute( *this );
            }


            inline virtual ~Filter() noexcept {}

            template <typename PIXEL> inline
            void load(const Pixmap<PIXEL> &source,
                      const Point          origin)
            {
                const FilterElement<T> * elem = & (*this)[1];
                for(size_t i=this->size();i>0;--i,++elem)
                {
                    const Point p = origin + elem->p;
                    const PIXEL c = source[p];
                }

            }


            Additions adds;  //!< additions
            const T   wsum; //!< sum of weights


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
    std::cerr << F << "/" << F.wsum << std::endl;


    Filter<int> Fi( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fi<< "/" << Fi.wsum << std::endl;

    Filter<uint32_t> Fu( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fu<< "/" << Fu.wsum << std::endl;
}
Y_UDONE()
