#include "y/calculus/isqrt.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

using namespace Yttrium;

Y_UTEST(calculus_isqrt)
{

    for(int i=0;i<=100;++i)
    {
        const int s = IntegerSquareRoot(i);
        std::cerr << i << " => " << s << std::endl;
        Y_ASSERT(s*s<=i);
        Y_ASSERT((s+1)*(s+1)>i);
    }

    Y_PRINTV(Calculus::IntegerSquareRoot::TableBytes);
    Y_PRINTV(Calculus::IntegerSquareRoot::TableSize);

    {
        OutputFile fp("isqrt.hxx");
        for(unsigned i=0;i<Calculus::IntegerSquareRoot::TableSize;++i)
        {
            const unsigned s = IntegerSquareRoot(i);
            fp("%u",s);
            if(i<Calculus::IntegerSquareRoot::TableLast)
                fp << ',';
            fp << '\n';
        }
    }



}
Y_UDONE()

