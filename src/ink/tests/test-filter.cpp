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
            typedef FilterElement<T>   Element;
            typedef CxxSeries<Element> Elements;
            typedef Cameo::Addition<T> Addition;
            typedef Cameo::Caddy<T>    Additions;

            using Elements::capacity;
            using Elements::size;

            template <typename U>
            inline explicit Filter(const U   * const blockAddr,
                                   const size_t      blockSize,
                                   const size_t      nChannels = 0) :
            FilterMetrics(blockSize),
            CxxSeries< FilterElement<T> >( Count(blockAddr,blockSize) ),
            adds( nChannels, capacity() ),
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


            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void load(T * const            target,
                      const Pixmap<PIXEL> &source,
                      const Point          origin)
            {
                assert(adds.size>=NCHAN);
                adds.ldz();
                {
                    const Element * elem = & (*this)[1];
                    for(size_t i=size();i>0;--i,++elem)
                        acc<PTYPE,NCHAN>( (const PTYPE *) &source[origin + elem->p], elem->w);
                }
                sum<NCHAN>(target);
            }

            Additions adds; //!< additions
            const T   wsum; //!< sum of weights

        private:
            Y_Disable_Copy_And_Assign(Filter);

            template <typename PTYPE, const size_t NCHAN> inline
            void acc(const PTYPE * const ptype, const T w)
            {
                assert(adds.size>=NCHAN);
                Addition * add   = adds.head;
                for(size_t j=0;j<NCHAN;++j,add=add->next)
                {
                    assert(0!=add);
                    add->addProd(w,ptype[j]);
                }
            }

            template <const size_t NCHAN>
            void sum(T * const target)
            {
                assert(adds.size>=NCHAN);
                Addition * add   = adds.head;
                for(size_t j=0;j<NCHAN;++j,add=add->next)
                {
                    assert(0!=add);
                    target[j] = add->sum();
                }
            }
        };

        template <typename SCALAR>
        struct ApplyFilter
        {
            template <typename T> static inline
            void Fill(T                    & target,
                      Filter<T>            & filter,
                      const Pixmap<SCALAR> & source,
                      const Point            point)
            {
                filter.template load<SCALAR,SCALAR,1>(&target,source,point);
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
    std::cerr << F << "/" << F.wsum << std::endl;


    Filter<int> Fi( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fi<< "/" << Fi.wsum << std::endl;

    Filter<uint32_t> Fu( &f[0][0], sizeof(f)/sizeof(f[0][0]) );
    std::cerr << Fu<< "/" << Fu.wsum << std::endl;

    Pixmap<uint8_t> pxm(200,100);

    float target = 0;
    ApplyFilter<uint8_t>::Fill(target,F,pxm,Point(0,0));

}
Y_UDONE()
