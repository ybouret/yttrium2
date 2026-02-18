#include "y/utest/run.hpp"
#include "y/container/algorithm/unique.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/sorting/heap.hpp"
#include "y/container/cxx/series.hpp"
#include "y/calculus/iabs.hpp"
#include "y/core/utils.hpp"
#include "y/cameo/addition.hpp"

#include "y/ink/ops/filter/element.hpp"
#include "y/ink/ops.hpp"
#include <cstring>

using namespace Yttrium;


namespace Yttrium
{
    namespace Ink
    {

        class BlurMetrics
        {
        public:
            explicit BlurMetrics(const unit_t rmax);
            virtual ~BlurMetrics() noexcept;

            size_t count() const;

            const unit_t r;
            const unit_t r2;

        private:
            Y_Disable_Copy_And_Assign(BlurMetrics);
        };

        BlurMetrics:: BlurMetrics(const unit_t rmax) :
        r( IntegerAbs(rmax) ),
        r2(r*r)
        {
        }

        BlurMetrics:: ~BlurMetrics() noexcept
        {

        }


        size_t BlurMetrics:: count() const
        {
            size_t res = 0;
            for(unit_t y=-r;y<=r;++y)
            {
                const unit_t y2 = y*y;
                for(unit_t x=-r;x<=r;++x)
                {
                    if(x*x+y2<=r2) ++res;
                }
            }

            return res;
        }



        template <typename T>
        class Blur : public BlurMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            typedef FilterElement<T>   Element;
            typedef CxxSeries<Element> Elements;
            typedef TypeToType<T>      MyTypeHint;

            template <typename PROC>
            explicit Blur(PROC &proc, const unit_t rmax) :
            BlurMetrics(rmax),
            Elements(count()),
            denom(0)
            {
                Cameo::Addition<T>  add;
                for(unit_t y=-r;y<=r;++y)
                {
                    const unit_t y2 = y*y;
                    for(unit_t x=-r;x<=r;++x)
                    {
                        const unit_t ir2 = x*x+y2;
                        if(ir2<=r2)
                        {
                            const Point p(x,y);
                            const T     w = proc( (T)ir2 );
                            if(w<=denom) throw Specific::Exception("Blur", "invalid weight");
                            add << w;
                            this->push(p,w);
                        }
                    }
                }
                Coerce(denom) = add.sum();
                Sorting::Heap::Sort( (*this)(), this->size(), Element::Compare);
            }

            template <
            typename       PIXEL,
            typename       PTYPE,
            const unsigned NCHAN
            >
            void load(PTYPE * const        target,
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


            virtual ~Blur() noexcept
            {
            }

            const T       denom;


        private:
            Y_Disable_Copy_And_Assign(Blur);

        };

        float g(const float r2)
        {
            return expf(-r2/10.0f);
        }

    }
}



#include "y/stream/libc/output.hpp"

Y_UTEST(blur)
{
    Ink::Blur<float> blur(Ink::g,5);
    std::cerr << "blur=" << blur << std::endl;

}
Y_UDONE()

