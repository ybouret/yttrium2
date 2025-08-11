


#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"
#include "y/string/env.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/jive/lexical/plugin/rstring.hpp"
#include "y/jive/lexical/plugin/bstring.hpp"

#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"

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


            plug(Lexical::JString::Class,"jString");
            plug(Lexical::RString::Class,"rString");
            plug(Lexical::BString::Class,"bString");

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
    {
        OutputFile fp("lexer.bin");
        lexer.serialize(fp);
    }
    {
        InputFile fp("lexer.bin");
        Lexer::Load(fp);
    }
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
        std::cerr << lx->str() << ' ' << *lx << " = '" << lx->toString() << "'"  << std::endl;
    }
}
Y_UDONE()
