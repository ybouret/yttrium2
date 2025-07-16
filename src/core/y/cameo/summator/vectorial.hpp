
//! \file

#ifndef Y_Cameo_VectorialSummator_Included
#define Y_Cameo_VectorialSummator_Included 1

#include "y/cameo/summator/scalar.hpp"
#include "y/memory/operating.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        template <typename T>
        class VectorialSummator : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);
            typedef typename MKL::ScalarFor<T>::Type ScalarType;
            typedef ScalarSummator<ScalarType>       CoordSummator;

            static const size_t DIMENSIONS = MutableType::DIMENSIONS;

            inline explicit VectorialSummator() :
            Summator<T>(),
            summators(DIMENSIONS),
            operating(summators.entry,DIMENSIONS)
            {}

            inline virtual ~VectorialSummator() noexcept
            {
            }

            inline explicit VectorialSummator(const size_t n) :
            Summator<T>(),
            summators(DIMENSIONS),
            operating(CopyOf,n,summators.entry,DIMENSIONS)
            {}

            inline virtual void ldz() noexcept
            {
                for(size_t i=0;i<DIMENSIONS;++i) summators.entry[i].ldz();
            }

            inline virtual T sum() {
                try
                {
                    T res;
                    {
                        ScalarType * const coord = Memory::Stealth::Cast<ScalarType>( &res );
                        for(size_t i=0;i<DIMENSIONS;++i)
                            coord[i] = summators.entry[i].sum();
                    }
                    ldz();
                    return res;
                }
                catch(...)
                {
                    ldz();
                    throw;
                }
            }


        private:
            Y_Disable_Copy_And_Assign(VectorialSummator);
            Memory::SchoolOf<CoordSummator>   summators;
            Memory::Operating<CoordSummator>  operating;
            inline virtual void add(ParamType value)
            {
                try {
                    const ScalarType * const coord = Memory::Stealth::Cast<ScalarType>( &value );
                    for(size_t i=0;i<DIMENSIONS;++i)
                        summators.entry[i] << coord[i];
                }
                catch(...)
                {
                    ldz();
                    throw;
                }
            }
        };
    }

}

#endif

