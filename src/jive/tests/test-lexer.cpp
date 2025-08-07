


#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"
#include "y/string/env.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{
    class MyLexer : public Lexer
    {
    public:
        explicit MyLexer() : Lexer("MyLexer")
        {
            emit("int",  "[:digit:]+");
            emit("word", "[:word:]+");

            comment("C++ Comment","//");
            comment("C Comment","/\\*", "\\*/");

            new Lexical::JString("string",*this);
            
            endl("endl",  "[:endl:]");
            drop("blank", "[:blank:]");
        }

        virtual ~MyLexer() noexcept
        {

        }

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };
}

Y_UTEST(lexer)
{
    Lexical::Scanner::Verbose = Environment::Flag("VERBOSE");
    MyLexer lexer;

    Lexemes lxm;
    if(argc>1)
    {
        Source source( Module::OpenFile( argv[1] ) );
        while(Lexeme *lx = lexer.query(source) )
        {
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
