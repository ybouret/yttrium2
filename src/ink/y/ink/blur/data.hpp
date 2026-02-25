
//! \file

#ifndef Y_Ink_Blur_Data_Included
#define Y_Ink_Blur_Data_Included 1

#include "y/ink/blur/metrics.hpp"
#include "y/ink/filter/element.hpp"
#include "y/container/cxx/series.hpp"
#include "y/exception.hpp"
#include "y/cameo/addition.hpp"
#include "y/ink/pixmap.hpp"
#include "y/ink/colors.hpp"


namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Points and weights for function+radius
        //
        //
        //______________________________________________________________________
        template <typename T>
        class BlurData : public BlurMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef FilterElement<T>   Element;    //!< alias
            typedef CxxSeries<Element> Elements;   //!< alias
            typedef TypeToType<T>      MyTypeHint; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param proc proc(x^2+y^2) \param rmax radius
            template <typename PROC>
            explicit BlurData(PROC &proc, const unit_t rmax) :
            BlurMetrics(rmax),
            Elements(count()),
            denom(0),
            half(0.5)
            {
                Elements           & self = *this;
                Cameo::Addition<T>   add;
                const T              f0 = proc(0);
                for(unit_t y=-r;y<=r;++y)
                {
                    const unit_t y2 = y*y;
                    for(unit_t x=-r;x<=r;++x)
                    {
                        const unit_t ir2 = x*x+y2;
                        if(ir2<=r2)
                        {
                            const Point p(x,y);
                            const T     w = proc( ir2 )/f0;
                            if(w<=denom) throw Specific::Exception("Blur", "invalid weight");
                            add << w;
                            self.push(p,w);
                        }
                    }
                }
                Coerce(denom) = add.sum();
                Sorting::Heap::Sort(self,Element::Compare);
            }


            //! cleanup
            virtual ~BlurData() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! apply to Pixmap<T> at given point: raw average
            /**
             \param target target
             \param source source
             \param origin origin
             */
            void apply(Pixmap<T>       &target,
                       const Pixmap<T> &source,
                       const Point      origin)
            {
                // put direct result
                load<T,T,1>(&target[origin],source,origin);
            }

            //! apply to Pixmap<uint8_t> at given point: raw average+closest byte
            /**
             \param target target
             \param source source
             \param origin origin
             */
            void apply(Pixmap<uint8_t>       &target,
                       const Pixmap<uint8_t> &source,
                       const Point            origin)
            {
                // get result in T type
                T res = 0; load<uint8_t,uint8_t,1>(&res,source,origin);

                // convert to closest byte
                target[origin] = (uint8_t)floor(res+half);
            }

            //! apply to Pixmap<RGBA> at given point: raw average+closest byte per channel
            /**
             \param target target
             \param source source
             \param origin origin
             */
            void apply(Pixmap<RGBA>       &target,
                       const Pixmap<RGBA> &source,
                       const Point         origin)
            {
                // get result in T types
                T res[3] = {0,0,0};
                load<RGBA,uint8_t,3>(res,source,origin);

                // convert to closest bytes
                RGBA &c = target[origin];
                c.r = (uint8_t)floor(res[0]+half);
                c.g = (uint8_t)floor(res[1]+half);
                c.b = (uint8_t)floor(res[2]+half);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const T denom; //!< sum of weights
            const T half;  //!< 0.5

        private:
            Y_Disable_Copy_And_Assign(BlurData); //!< discarding

            //! compute result in T values
            /**
             \param target target[NCHAN]
             \param source source pixmap
             \param origin probe point
             */
            template <
            typename       PIXEL,
            typename       PTYPE,
            const unsigned NCHAN
            >
            inline void load(T * const            target,
                             const Pixmap<PIXEL> &source,
                             const Point          origin)
            {
                {
                    const Elements &self = *this;
                    memset(target,0,sizeof(PTYPE)*NCHAN);
                    for(size_t i=self.size();i>0;--i)
                    {
                        static const MyTypeHint MyType = {};
                        const Element &         elem   = self[i];
                        const PTYPE * const     ptype  = (const PTYPE *) &source[origin+elem.p];
                        const T                 weight = elem.w;
                        for(size_t j=0;j<NCHAN;++j) {
                            target[j] += MKL::AdaptedTo(MyType,ptype[j]) * weight;
                        }
                    }
                }
                for(size_t j=0;j<NCHAN;++j) target[j] /= denom;
            }

        };

    }

}

#endif // !Y_Ink_Blur_Data_Included

