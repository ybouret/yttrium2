#include "y/jive/pattern/basic/all.hpp"
#include "y/jive/pattern/joker/all.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

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

        {
            const String binName = name + ".bin";
            OutputFile   fp(binName);
            const size_t written = p->serialize(fp);
            std::cerr << "\twritten: " << written << std::endl;
        }
    }

}

Y_UTEST(pattern)
{
    testPattern(new Single('a'));
    testPattern(new Range('0','9'));

    {
        const Motif m = new Range('a','z');
        testPattern( new Option(m) );
    }


}
Y_UDONE()
