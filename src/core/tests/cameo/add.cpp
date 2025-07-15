#include "y/cameo/addition.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"


using namespace Yttrium;

namespace Yttrium
{
    namespace Cameo
    {

        template <typename T>
        class ScalarSummator : public Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API
        {
        public:
            typedef typename Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API SummatorType; //!< alias

            explicit ScalarSummator() : SummatorType()
            {
            }

            virtual ~ScalarSummator() noexcept
            {
                
            }

        private:
            Y_Disable_Copy_And_Assign(ScalarSummator);
        };

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

Y_UTEST(cameo_add)
{

    {
        Cameo::DirectSummator<apz> zsum;
        Cameo::DirectSummator<apn> nsum;

        Cameo::AProxySummator<int>            isum; std::cerr << "isum/" <<Cameo::AProxySummator<int>::CoreType::CallSign << std::endl;
        Cameo::AProxySummator<unsigned short> usum; std::cerr << "usum/" <<Cameo::AProxySummator<unsigned short>::CoreType::CallSign << std::endl;


        Cameo::FPointSummator< float > fsum(5);
        std::cerr << fsum->capacity() << std::endl;
        fsum->ensure(10);
        std::cerr << fsum->capacity() << std::endl;

        fsum->release();

        fsum << -0.01f << 0.02f << 1.0f << -1.2f;

        //std::cerr << "fsum=" << fsum << std::endl;
        std::cerr << "Computing" << std::endl;
        const float s = fsum.sum();
        std::cerr << "s=" << s << std::endl;


        Cameo::FPointSummator< XReal<long double> > xsum(5);
        xsum << -0.01 << 0.02 << 1 << -1.2;
        std::cerr << "Computing" << std::endl;
        const  XReal<long double> x = xsum.sum();
        std::cerr << "x=" << x << std::endl;

        Cameo::FPointSummator< Complex<double> > csum(5);
        csum << -0.01 << 0.02 << 1 << -1.2;
        std::cerr << "Computing" << std::endl;
        const Complex<double> c = csum.sum();
        std::cerr << "c=" << c << std::endl;
    }

    {
        Cameo::Addition<apz>                zsum;
        Cameo::Addition<apn>                nsum;
        Cameo::Addition<int>                isum;
        Cameo::Addition<unsigned>           usum;
        Cameo::Addition<float>              fsum;
        Cameo::Addition< XReal<double> >    xsum;
        Cameo::Addition< Complex<double> >  csum;
        Cameo::Addition< Complex< XReal<long double> > >  xcsum;
    }


    {
        Cameo::VectorialSummator< Complex<float> > csum;
    }
}
Y_UDONE()



