#include "y/jive/pattern/basic/all.hpp"
#include "y/jive/pattern/joker/all.hpp"
#include "y/jive/pattern/logic/all.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;
using namespace Jive;

namespace  {

    static inline
    void testPattern(Pattern *p, const char * const attr = 0)
    {
        const String extra = attr;
        Motif motif(p);
        const String name = FourCC(p->uuid).c_str() + extra;
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

        const FirstChars fc = p->firstChars();
        std::cerr << "\tfc: " << fc << std::endl;
    }

}

Y_UTEST(pattern)
{
    testPattern(new Single('a') );
    testPattern(new Range('0','9') );

    {
        const Motif m = new Range('a','z');
        testPattern( new Option(m) );
    }

    {
        const Motif m = new Range('0','1');
        testPattern( new Repeat(m,0), "0");
        testPattern( new Repeat(m,1), "1");
        testPattern( new Repeat(m,7), "N");
    }

    {
        const Motif m = new Single('b');
        testPattern( new Amount(m,0,3) );
    }

    {
        AutoPtr<Logic> p = new And();
        *p << new Single('a');
        *p << new Range('0','9');
        testPattern( p.yield() );
    }

    {
        AutoPtr<Logic> p = new Or();
        *p << new Single('a');
        *p << new Range('0','9');
        testPattern( p.yield() );
    }

    {
        AutoPtr<Logic> p = new None();
        *p << new Single('a');
        *p << new Range('0','9');
        testPattern( p.yield() );
    }



}
Y_UDONE()
