

#include "y/jive/lexical/scanner.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Jive;

namespace
{
   
}
Y_UTEST(scanner)
{
    Lexical::Scanner scan("Scanner");
    scan.decl("ID","[:alpha:]+",   Lexical::Regular, true, 0);
    scan.decl("INT","[:digit:]+",  Lexical::Regular, true, 0);
    scan.decl("FLT","[:digit:]+\\.[:digit:]*",Lexical::Regular, true,0);
    scan.decl("dot", ".",          Lexical::Regular, true, 0);
    scan.decl("endl", "[:endl:]",  Lexical::NewLine, false, 0);

    Lexemes lxm;
    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        while(Lexeme *lx=scan(source))
        {
            std::cerr << "Found " << *lx << std::endl;
            lxm.pushTail(lx);
        }


    }
    std::cerr << "lexemes:" << std::endl;
    for(const Lexeme *lx=lxm.head;lx;lx=lx->next)
    {
        std::cerr << lx->str() << ' ' << *lx << std::endl;
    }


}
Y_UDONE()
