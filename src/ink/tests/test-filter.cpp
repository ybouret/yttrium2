



#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/series.hpp"

#include "y/calculus/isqrt.hpp"
#include "y/format/decimal.hpp"
#include "y/apex/integer.hpp"

#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace Ink
    {


        class FilterMetrics
        {
        public:
            static const char * const CallSign;

            explicit FilterMetrics(const size_t blockSize);
            virtual ~FilterMetrics() noexcept;

            template <typename T> static inline
            size_t Count(const T * const blockAddr, const size_t blockSize)
            {
                assert(0!=blockAddr);
                size_t res = 0;
                for(size_t i=0;i<blockSize;++i)
                {
                    switch( Sign::Of(blockAddr[i]) )
                    {
                        case __Zero__: continue;
                        case Negative:
                        case Positive:
                            ++res;
                            continue;
                    }
                }
                return res;
            }

            const size_t side;
            const unit_t delta;

        private:
            Y_Disable_Copy_And_Assign(FilterMetrics);
        };


        const char * const FilterMetrics :: CallSign = "Ink::FilterMetrics";

        FilterMetrics:: FilterMetrics(const size_t blockSize)   :
        side( IntegerSquareRoot(blockSize) ),
        delta( (side-1) >> 1 )
        {
            if(blockSize<=0)         throw Specific::Exception(CallSign,"no coefficient");
            if(side*side!=blockSize) throw Specific::Exception(CallSign,"%s is not a square", Decimal(blockSize).c_str());
            if(1!=(side&1))          throw Specific::Exception(CallSign,"side=%s is not odd", Decimal(side).c_str());
        }

        FilterMetrics:: ~FilterMetrics() noexcept
        {
        }




        template <typename T> class FilterElement
        {
        public:
            inline  FilterElement(const Point _p, const T _w) : p(_p),  w(_w) {}
            inline ~FilterElement() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const FilterElement &self)
            {
                os << '@' << self.p << "=" << self.w;
                return os;
            }

            const Point p;
            const T     w;



        private:
            Y_Disable_Copy_And_Assign(FilterElement);
        };



        template <typename T>
        class FilterSumF : public Cameo::Addition<T>
        {
        public:
            inline explicit FilterSumF(const size_t n) : Cameo::Addition<T>(n)
            {
            }

            inline virtual ~FilterSumF() noexcept {}

            inline T operator()(const Readable< FilterElement<T> > &elem)
            {
                this->ldz();
                for(size_t i=elem.size();i>0;--i)
                    (*this) << elem[i].w ;
                return this->sum();
            }

        private:
            Y_Disable_Copy_And_Assign(FilterSumF);
        };

        template <typename T, typename A>
        class FilterSumA
        {
        public:
            inline explicit FilterSumA() : sum(0)
            {
            }

            inline virtual ~FilterSumA() noexcept {}


            inline T operator()(const Readable< FilterElement<T> > &elem)
            {
                sum = 0;
                for(size_t i=elem.size();i>0;--i)
                    sum += elem[i].w;
                return sum.template cast<T>(NULL); // TODO
            }

            A sum;
        private:
            Y_Disable_Copy_And_Assign(FilterSumA);
        };


        template <typename T>
        struct FilterSum
        {
            static const bool IsIsoFloatingPoint = TypeTraits<T>::IsIsoFloatingPoint;
            static const bool InIntegers         = TypeTraits<T>::InStandardIntegers || TypeTraits<T>::InPlatformIntegers;
            static const bool InUnsigned         = TypeTraits<T>::InStandardUnsigned || TypeTraits<T>::InPlatformUnsigned;
            static const unsigned IsF   = 0x01;
            static const unsigned IsI   = 0x02;
            static const unsigned IsU   = 0x04;
            static const unsigned FFlag = IsIsoFloatingPoint ? IsF : 0x00;
            static const unsigned IFlag = InIntegers         ? IsI : 0x00;
            static const unsigned UFlag = InUnsigned         ? IsU : 0x00;
            static const unsigned Flags = FFlag | IFlag | UFlag;

            static inline T Compute( const Readable< FilterElement<T> > &elem )
            {
                static const IntToType<Flags> Choice = {};
                return Compute(elem,Choice);
            }

        private:

            static inline T Compute( const Readable< FilterElement<T> > &elem, const IntToType<IsF> &)
            {
                FilterSumF<T> sum( elem.size() );
                return sum(elem);
            }

            static inline T Compute( const Readable< FilterElement<T> > &elem, const IntToType<IsI> &)
            {
                FilterSumA<T,apz> sum;
                return sum(elem);
            }

            static inline T Compute( const Readable< FilterElement<T> > &elem, const IntToType<IsU> &)
            {
                FilterSumA<T,apn> sum;
                return sum(elem);
            }

        };


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


}
Y_UDONE()
