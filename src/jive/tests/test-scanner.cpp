

#include "y/jive/lexical/scanner.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Jive;

namespace
{
    class MyScanner : public Lexical::Scanner
    {
    public:
        explicit MyScanner(const Lexical::Design &com) :
        Scanner("Scanner",com,Lexical::AcceptEOF)
        {
            decl("ID",   "[:alpha:]+",   Lexical::Regular, true);
            decl("INT",  "[:digit:]+",   Lexical::Regular, true);
            decl("FLT",  "[:digit:]+\\.[:digit:]*",Lexical::Regular, true);
            decl("dot",  ".",          Lexical::Regular, true);
            decl("endl", "[:endl:]",   Lexical::NewLine, false);
        }

        virtual ~MyScanner() noexcept
        {
        }

        virtual void onCall(const Token &) {}
        virtual void onBack(const Token &) {}
        
    private:
        Y_Disable_Copy_And_Assign(MyScanner);
    };
}


Y_UTEST(scanner)
{
    Dictionary::Pointer pdb = new Dictionary();
    Lexical::Design     com;
    MyScanner           scan(com);

    Lexemes lxm;
    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        AutoPtr<Lexeme> lx = 0;
        const String *  id = 0;

        while( Lexical::EmitUnit == scan.run(source,lx,id) )
        {
            Y_ASSERT(lx.isValid());
            Y_ASSERT(0==id);
            lxm.pushTail(lx.yield());
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
