#if 0
//! \file

#ifndef Y_Ink_Filter_Sum_Included
#define Y_Ink_Filter_Sum_Included 1

#include "y/ink/ops/filter/element.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace Ink
    {
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

    }

}

#endif // !Y_Ink_Filter_Sum_Included
#endif

