


#include "y/jive/pattern/basic.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

namespace  {

    static inline
    void testPattern(Pattern *p)
    {
        Motif motif(p);
        const String name = FourCC(p->uuid).c_str();
        std::cerr << name << std::endl;


        {
            const String dotName = name + ".dot";
            Vizible::Render(dotName,*p);
        }

    }

}

Y_UTEST(pattern)
{
    testPattern(new Single('a'));
    testPattern(new Range('0','9'));

}
Y_UDONE()
