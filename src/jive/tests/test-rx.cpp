

#include "y/jive/regexp.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(rx)
{
    if(argc>1)
    {

        std::cerr << "compiling '" << argv[1] << "'" << std::endl;
        const Motif motif = RegExp::Compile(argv[1],0);

        {
            const String dotName = "rx.dot";
            Vizible::Render(dotName,*motif);
        }


    }
}
Y_UDONE()
