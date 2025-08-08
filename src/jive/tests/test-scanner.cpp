

#include "y/jive/lexical/scanner.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{
    class MyScanner : public Lexical::Scanner
    {
    public:
        explicit MyScanner(const Lexical::Design &com) :
        Scanner(0x00,"Scanner",com,Lexical::AcceptEOF)
        {
            emit("ID",   "[:alpha:]+");
            emit("INT",  "[:digit:]+");
            emit("FLT",  "[:digit:]+\\.[:digit:]*");
            emit("dot",  ".");
            endl("endl", "[:endl:]");
        }

        virtual ~MyScanner() noexcept
        {
        }

        virtual void onCall(Token &) {}
        virtual void onBack(Token &) {}
        virtual void onSent(Token &) {}

    private:
        Y_Disable_Copy_And_Assign(MyScanner);
    };
}


Y_UTEST(scanner)
{
    Lexical::Design     com;
    MyScanner           scan(com);

    {
        OutputFile fp("scanner.bin");
        scan.serialize(fp);
    }


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
