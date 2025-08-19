#include "y/jive/syntax/grammar.hpp"
#include "y/utest/run.hpp"
#include "y/vfs/local/fs.hpp"

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
            emit("ID","[:alpha:][:word:]*");
            emit('=');
            comment("Shell Comment","#");
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
        explicit MyGrammar() : Syntax::Grammar("MyGrammar",0)
        {
            Alt        & TOP    = alt("TOP");
            const Rule & INT    = terminal("INT");
            const Rule & EQ     = terminal('=');
            const Rule & ID     = terminal("ID");
            const Rule & ASSIGN = cat(ID,EQ,INT);
            TOP << ASSIGN << ID << INT;

            
            Render("grammar.dot",*this);
            validate();
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
    Syntax::Rule::Verbose = true;
    MyGrammar G;
    MyLexer   L;
    LocalFS  &fs = LocalFS::Instance();

    fs.tryRemoveFile("tree.dot");
    fs.tryRemoveFile("tree.png");

    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        AutoPtr<Syntax::Node> tree = G.run(L,source);
        Y_ASSERT(tree.isValid());
        Vizible::Render("tree.dot",*tree);
    }
}
Y_UDONE()

