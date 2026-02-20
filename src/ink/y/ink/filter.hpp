

//! \file

#ifndef Y_Ink_Filter_Included
#define Y_Ink_Filter_Included 1

#include "y/ink/filter/metrics.hpp"
#include "y/ink/filter/element.hpp"
#include "y/cameo/caddy.hpp"
#include "y/container/cxx/series.hpp"


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
            adds( nChannels, capacity() )
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
                assert(adds.size>=NCHAN);
                adds.ldz();
                {
                    const Element * elem = & (*this)[1];
                    for(size_t i=size();i>0;--i,++elem)
                        acc<PTYPE,NCHAN>( (const PTYPE *) &source[origin + elem->p], elem->w);
                }
                sum<NCHAN>(target);
            }



            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void loadTranspose(T * const            target,
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

            template <typename SCALAR>
            void applyImmediate(Pixmap<float>        & target,
                                const Pixmap<SCALAR> & source,
                                const Point           origin)
            {
                loadImmediate<SCALAR,SCALAR,1>( &target[origin], source, origin);
            }

            

            Additions adds; //!< additions

        private:
            Y_Disable_Copy_And_Assign(Filter);

            //! accumulate PTYPE[NCHAN] in additions
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

            //! place each addition in target[NCHAN]
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
    }

}

#endif // !Y_Ink_Filter_Included

