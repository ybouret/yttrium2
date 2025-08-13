#include "y/jive/syntax/grammar.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{
    class MyLexer : public Lexer
    {
    public:
        explicit MyLexer() : Lexer("MyLexer")
        {
            emit("INT","[:digit:]+");

            drop("[:blank:]");
            endl("[:endl:]",false);
        }

        virtual ~MyLexer() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };

    class MyGrammar : public Syntax::Grammar
    {
    public:
        explicit MyGrammar() : Syntax::Grammar("MyGrammar")
        {
            const Rule & INT = terminal("INT");
            Y_ASSERT( & top() == & INT );
        }

        virtual ~MyGrammar() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(MyGrammar);
    };

}


Y_UTEST(grammar)
{
    MyGrammar G;
    MyLexer   L;

    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        AutoPtr<Syntax::Node> tree = G.run(L,source);

    }
}
Y_UDONE()

