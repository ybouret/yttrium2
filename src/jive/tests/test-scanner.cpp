

#include "y/jive/lexical/scanner.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Jive;

namespace
{
   
}
Y_UTEST(scanner)
{
    Dictionary::Pointer pdb = new Dictionary();
    Lexical::Scanner    scan("Scanner",pdb);
    scan.decl("ID","[:alpha:]+",   Lexical::Regular, true);
    scan.decl("INT","[:digit:]+",  Lexical::Regular, true);
    scan.decl("FLT","[:digit:]+\\.[:digit:]*",Lexical::Regular, true);
    scan.decl("dot", ".",          Lexical::Regular, true);
    scan.decl("endl", "[:endl:]",  Lexical::NewLine, false);

    Lexemes lxm;
    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        Lexeme *       lx = 0;
        const String * id = 0;

        while( Lexical::EmitUnit == scan(source,lx,id) )
        {
            Y_ASSERT(0!=lx);
            Y_ASSERT(0==id);
            lxm.pushTail(lx);
            lx = 0;
        }


    }
    std::cerr << "lexemes:" << std::endl;
    for(const Lexeme *lx=lxm.head;lx;lx=lx->next)
    {
        std::cerr << lx->str() << ' ' << *lx << std::endl;
    }


}
Y_UDONE()
