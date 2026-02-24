

//! \file

#ifndef Y_Ink_Filter_Included
#define Y_Ink_Filter_Included 1

#include "y/ink/filter/metrics.hpp"
#include "y/ink/filter/element.hpp"
#include "y/ink/pixmap.hpp"
#include "y/container/cxx/series.hpp"
#include "y/mkl/api/adaptor.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Square Filter
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Filter : public FilterMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef FilterElement<T>   Element;  //!< alias
            typedef CxxSeries<Element> Elements; //!< alias

            using Elements::capacity;
            using Elements::size;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup using "decreasing y-filter" representation
            /**
             \param blockAddr values
             \param blockSize number of values
             */
            template <typename U>
            inline explicit Filter(const U   * const blockAddr,
                                   const size_t      blockSize) :
            FilterMetrics(blockSize),
            CxxSeries< FilterElement<T> >( Count(blockAddr,blockSize) )
            {
                size_t i=0;
                for(unit_t y=delta;y>=-delta;--y)
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

            //! cleanup
            inline virtual ~Filter() noexcept {}


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! apply filter
            /**
             \param target target[NCHAN]
             \param source source pixmap
             \param origin probe point
             */
            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void loadImmediate(T * const            target,
                               const Pixmap<PIXEL> &source,
                               const Point          origin) const
            {
                memset(target,0,NCHAN*sizeof(T));
                const Element * elem = & (*this)[1];
                for(size_t i=size();i>0;--i,++elem)
                    acc<PTYPE,NCHAN>(target,(const PTYPE *) &source[origin + elem->p], elem->w);
            }

            //! apply filter of transpose positions
            /**
             \param target target[NCHAN]
             \param source source pixmap
             \param origin probe point
             */
            template <
            typename     PIXEL,
            typename     PTYPE,
            const size_t NCHAN>
            inline
            void loadTranspose(T * const            target,
                               const Pixmap<PIXEL> &source,
                               const Point          origin) const
            {
                memset(target,0,NCHAN*sizeof(T));
                const Element * elem = & (*this)[1];
                for(size_t i=size();i>0;--i,++elem)
                    acc<PTYPE,NCHAN>(target,(const PTYPE *) &source[origin + elem->p.transpose()], elem->w);
            }

            //! apply filter on scalar pixmap
            /**
             \param target target
             \param source scalar source
             \param origin probe point
             */
            template <typename SCALAR> inline
            void loadImmediateScalar(Pixmap<T>            & target,
                                     const Pixmap<SCALAR> & source,
                                     const Point            origin) const
            {
                loadImmediate<SCALAR,SCALAR,1>( &target[origin], source, origin);
            }

            //! apply tranpose filter on scalar pixmap
            /**
             \param target target
             \param source scalar source
             \param origin probe point
             */
            template <typename SCALAR> inline
            void loadTransposeScalar(Pixmap<T>            & target,
                                     const Pixmap<SCALAR> & source,
                                     const Point            origin) const
            {
                loadTranspose<SCALAR,SCALAR,1>( &target[origin], source, origin);
            }

            //! apply filter on both direction to deduce gradient
            /**
             \param amplitude gradient amplitude
             \param direction gradient direction
             \param field     scalar field
             \param origin probe point
             \return gradient amplitude at probe point
             */
            template <typename SCALAR> inline
            T loadGradient(Pixmap<T>            & amplitude,
                           Pixmap< V2D<T> >     & direction,
                           const Pixmap<SCALAR> & field,
                           const Point            origin) const
            {
                T gx = 0, gy = 0;

                // accumulate components
                {
                    const Element * elem = & (*this)[1];
                    for(size_t i=size();i>0;--i,++elem)
                    {
                        const T     w = elem->w;
                        const Point p = elem->p;
                        gy += w * field[origin+p];
                        gx += w * field[origin+p.transpose()];
                    }
                }

                // deduce gradient
                const T  g2 = gx*gx + gy*gy;
                T      & a = amplitude[origin];
                V2D<T> & v = direction[origin];

                if(g2<=0)
                {
                    a   = 0;
                    v.x = 0;
                    v.y = 0;
                    return 0;
                }
                else
                {
                    a   = sqrt(g2);
                    v.x = gx/a;
                    v.y = gy/a;
                    return a;
                }
            }





        private:
            Y_Disable_Copy_And_Assign(Filter); //!< discarding

            //! accumulate channel-wise elements
            /**
             \param target target[NCHAN]
             \param ptype  ptype[NCHAN]
             \param w      current weight
             */
            template <typename PTYPE, const size_t NCHAN> inline
            void acc(T * const target, const PTYPE * const ptype, const T w) const
            {
                static const TypeToType<T> MyType = {};
                for(size_t j=0;j<NCHAN;++j)
                {
                    target[j] += w * MKL::AdaptedTo(MyType,ptype[j]);
                }
            }


        };
    }

}

//! helper
#define Y_Ink_Filter_From(CLASS) & (CLASS::Table[0][0]), sizeof(CLASS::Table)/sizeof(CLASS::Table[0][0])

#endif // !Y_Ink_Filter_Included

