
#include "y/utest/run.hpp"
#include "y/calculus/alignment.hpp"

using namespace Yttrium;

namespace
{
    template <size_t P>
    static inline
    void testAlign()
    {
        std::cerr << "Alignment On " << P << std::endl;
        typedef Alignment::On<P> Alignment;

        for(size_t i=0;i<=20;++i)
        {
            std::cerr << " / " << i << "->" << Alignment::Ceil(i);
        }
        std::cerr << std::endl;
        std::cerr << Alignment::template CeilOf<0>::Value << std::endl;
        std::cerr << Alignment::template CeilOf<10>::Value << std::endl;
        std::cerr << Alignment::template CeilOf<20>::Value << std::endl;
        std::cerr << Alignment::template CeilOf<30>::Value << std::endl;
        std::cerr << Alignment::template CeilOf<40>::Value << std::endl;

    }
}

Y_UTEST(calculus_alignment)
{
    testAlign<1>();
    testAlign<2>();
    testAlign<4>();
    testAlign<8>();

    Y_PRINTV( Alignment::WordsGEQ<1>::Count  );
    Y_PRINTV( Alignment::WordsGEQ<70>::Count );

}
Y_UDONE()
