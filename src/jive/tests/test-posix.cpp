#include "y/jive/pattern/posix.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;
using namespace Jive;


namespace
{
    static inline void testPosix(const char * const name,
                                 Pattern * const p)
    {
        assert(0!=p);
        AutoPtr<Pattern> motif = p;
        const String     root  = name;
        std::cerr << "rendering " << root << std::endl;

        {
            const String dotFile = root + ".dot";
            Vizible::Render(dotFile,*p);
        }
    }

#define Y_Jive_Posix(ID) testPosix(#ID, posix::ID() )

}

Y_UTEST(posix)
{

    Y_Jive_Posix(lower);
    Y_Jive_Posix(upper);
    Y_Jive_Posix(alpha);
    Y_Jive_Posix(digit);
    Y_Jive_Posix(alnum);
    Y_Jive_Posix(word);
    Y_Jive_Posix(xdigit);
    Y_Jive_Posix(blank);
    Y_Jive_Posix(space);
    Y_Jive_Posix(punct);
    Y_Jive_Posix(core);
    Y_Jive_Posix(vowel);
    Y_Jive_Posix(consonant);
    Y_Jive_Posix(endl);
    Y_Jive_Posix(dot);

}
Y_UDONE()
