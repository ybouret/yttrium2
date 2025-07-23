#include "y/graphviz/vizible.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;

Y_UTEST(graphviz)
{

    Vizible viz[256];
    int     c = 0;

    {
        OutputFile fp("table.dot");
        fp << "digraph G {\n";
        for(size_t i=0;i<16;++i)
        {
            for(size_t j=0;j<16;++j,++c)
            {
                const char C = c;
                viz[c].name(fp) << '[';
                Vizible::Endl(fp << ']');
                
                if(j>0)
                {
                    Vizible::Endl( viz[c-1].to( &viz[c], fp ) );
                }
            }
        }
        fp << "}\n";
    }

    system("dot -T png table.dot -o table.png");

}
Y_UDONE()

