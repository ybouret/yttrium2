


#include "y/jive/pattern/matching.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/input.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(matching)
{
    if(argc>1)
    {
        Matching match = argv[1];
        std::cerr << "first-chars: "<< match.fc << std::endl;

        if(argc>2)
        {
            InputFile fp(argv[2]);
            String    line;
            while(fp.gets(line))
            {
                std::cerr << "\texactly: ";
                {
                    const bool found = match.found(Matching::Exactly,line,line);
                    if(found) std::cerr << "'" << match <<  "'";
                    else      std::cerr << "NOT-FOUND";
                }
                std::cerr << std::endl;

                std::cerr << "\tsomehow: ";
                {
                    const bool found = match.found(Matching::Somehow,line,line);
                    if(found) std::cerr << "'" << match <<  "'";
                    else      std::cerr << "NOT-FOUND";
                }
                std::cerr << std::endl;
            }
        }
    }
}
Y_UDONE()
