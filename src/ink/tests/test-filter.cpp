



#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/series.hpp"

#include "y/calculus/isqrt.hpp"
#include "y/format/decimal.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class CoreFilter
        {
        public:
            static const char * const CallSign;

            explicit CoreFilter(const int * const blockAddr, const size_t blockSize);
            virtual ~CoreFilter() noexcept;


            const size_t ncof;
            const size_t side;
            const unit_t delta;

        private:
            Y_Disable_Copy_And_Assign(CoreFilter);
        };

        const char * const CoreFilter :: CallSign = "Ink::Filter";

        CoreFilter:: ~CoreFilter() noexcept
        {
        }

        CoreFilter:: CoreFilter(const int * const blockAddr, const size_t blockSize)   :
        ncof(0),
        side( IntegerSquareRoot(blockSize) ),
        delta( (side-1) >> 1 )
        {
            assert(0!=blockAddr);
            if(blockSize<=0)         throw Specific::Exception(CallSign,"no coefficient");
            if(side*side!=blockSize) throw Specific::Exception(CallSign,"%s is not a square", Decimal(blockSize).c_str());
            if(1!=(side&1))          throw Specific::Exception(CallSign,"side=%s is not odd", Decimal(side).c_str());

            for(size_t i=0;i<blockSize;++i)
            {
                if(blockAddr[i]) ++Coerce(ncof);
            }
        }

        template <typename T> class FilterElement
        {
        public:
            inline  FilterElement(const Coord _c, const T _w) : c(_c),  w(_w) {}
            inline ~FilterElement() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const FilterElement &self)
            {
                os << '@' << self.c << "=" << self.w;
                return os;
            }

            const Coord c;
            const T     w;

        private:
            Y_Disable_Copy_And_Assign(FilterElement);
        };


        template <typename T>
        class Filter : public CoreFilter, public CxxSeries< FilterElement<T> >
        {
        public:
            inline explicit Filter(const int * const blockAddr,
                                   const size_t      blockSize) :
            CoreFilter(blockAddr,blockSize),
            CxxSeries< FilterElement<T> >(ncof)
            {
                apz    sum = 0;
                size_t i=0;
                for(unit_t y=-delta;y<=delta;++y)
                {
                    for(unit_t x=-delta;x<=delta;++x)
                    {
                        const int w = blockAddr[i++];
                        if(!w) continue;
                        sum += w;
                        const T     W = (T) w;
                        const Coord C(x,y);
                        this->push(C,W);
                    }
                }
            }


            inline virtual ~Filter() noexcept {}



        private:
            Y_Disable_Copy_And_Assign(Filter);
        };

    }

}
using namespace Yttrium;
using namespace Ink;

Y_UTEST(filter)
{
    static const int f[3][3] =
    {
        { 1, 2, 3 },
        { 4, 5 ,6 },
        { 7, 8, 9 }
    };

    Filter<float> F(&f[0][0],sizeof(f)/sizeof(f[0][0]));
    std::cerr << "ncof=" << F.ncof << std::endl;
    std::cerr << F << std::endl;
}
Y_UDONE()
