
#include "y/utest/run.hpp"
#include "y/calculus/alignment.hpp"

#include "y/type/ints.hpp"

using namespace Yttrium;

namespace
{
    template <size_t P>
    static inline
    void testAlign()
    {
        std::cerr << "Alignment On " << P << std::endl;
        typedef Alignment::On<P> Align;

        for(size_t i=0;i<=20;++i)
        {
            std::cerr << " / " << i << "->" << Align::Ceil(i);
        }
        std::cerr << std::endl;
        Y_PRINTV(Align::template CeilOf<0>::Value);
        Y_PRINTV(Align::template CeilOf<10>::Value);
        Y_PRINTV(Align::template CeilOf<20>::Value);
        Y_PRINTV(Align::template CeilOf<30>::Value);
        Y_PRINTV(Align::template CeilOf<40>::Value);
        Y_PRINTV(Align::Inner::Maximum);
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

    //Y_PRINTV( Alignment:: On<8>:: Ceil( IntegerFor<size_t>::Maximum ) );


}
Y_UDONE()
