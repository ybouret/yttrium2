

//! \file

#ifndef Y_Ink_Filter_Included
#define Y_Ink_Filter_Included 1

#include "y/ink/filter/metrics.hpp"
#include "y/ink/filter/element.hpp"
#include "y/container/cxx/series.hpp"
#include "y/mkl/api/adaptor.hpp"


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

            using Elements::capacity;
            using Elements::size;

            template <typename U>
            inline explicit Filter(const U   * const blockAddr,
                                   const size_t      blockSize) :
            FilterMetrics(blockSize),
            CxxSeries< FilterElement<T> >( Count(blockAddr,blockSize) )
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
                Sorting::Heap::Sort(*this,Element::Compare);
            }



            inline virtual ~Filter() noexcept {}


            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void loadImmediate(T * const            target,
                               const Pixmap<PIXEL> &source,
                               const Point          origin)
            {
                memset(target,0,NCHAN*sizeof(T));
                const Element * elem = & (*this)[1];
                for(size_t i=size();i>0;--i,++elem)
                    acc<PTYPE,NCHAN>(target,(const PTYPE *) &source[origin + elem->p], elem->w);
            }


            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void loadTranpose(T * const            target,
                               const Pixmap<PIXEL> &source,
                               const Point          origin)
            {
                memset(target,0,NCHAN*sizeof(T));
                const Element * elem = & (*this)[1];
                for(size_t i=size();i>0;--i,++elem)
                    acc<PTYPE,NCHAN>(target,(const PTYPE *) &source[origin + elem->p.transpose()], elem->w);
            }

            


        private:
            Y_Disable_Copy_And_Assign(Filter);
            template <typename PTYPE, const size_t NCHAN> inline
            void acc(T * const target, const PTYPE * const ptype, const T w)
            {
                static const TypeToType<T> MyType = {};
                for(size_t j=0;j<NCHAN;++j)
                {
                    //xstd::cerr << "  + " << w << "*" << ptype[j] << std::endl;
                    target[j] += w * MKL::AdaptedTo(MyType,ptype[j]);
                }
            }


        };
    }

}

#endif // !Y_Ink_Filter_Included

