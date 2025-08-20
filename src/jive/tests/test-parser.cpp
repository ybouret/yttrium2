#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"

#include "y/jive/lexical/plugin/jstring.hpp"

#include "y/string/env.hpp"

#include "y/jive/analyzer.hpp"

using namespace Yttrium;


namespace
{
    class MyParser : public Jive::Parser
    {
    public:
        explicit MyParser() : Jive::Parser("JSON")
        {
            drop("[:blank:]");
            endl("[:endl:]",false);

            Alt &JSON = alt("JSON");

            Alt &Value = alt("Value");
            const Rule &JString = plugin( Jive::Lexical::JString::Class,"String");
            Value << JString;
            Value << term("Number","[:digit:]+");
            Value << "null" << "true" << "false";

            {
                Alt &Array = alt("Array");

                Array << (agg("EmptyArray")  << '[' << ']');
                Array << (agg("HeavyArray")  << '[' << Value << extra(',',Value) << ']');

                JSON  << Array;
                Value << Array;
            }

            {
                Alt        & OBJECT = alt("Object");
                const Rule & Pair  = ( agg("Pair") << JString << ':' << Value );
                OBJECT << ( agg("EmptyObject") << '{' << '}' );
                OBJECT << ( agg("HeavyObject") << '{' << Pair << extra(',',Pair) << '}');
                JSON << OBJECT;
                Value << OBJECT;
            }


            render();
            validate();
        }

        virtual ~MyParser() noexcept
        {

        }
    private:
        Y_Disable_Copy_And_Assign(MyParser);
    };

    class MyWalker : public Jive::Walker
    {
    public:
        explicit MyWalker(const Jive::Syntax::Grammar &G) : Jive::Walker(G)
        {
            Y_Jive_Push(MyWalker,Number);
        }

        virtual ~MyWalker() noexcept
        {

        }

        void onNumber(const Jive::Token &token)
        {
            std::cerr << "pushing Number " << token << std::endl;
        }


    private:
        Y_Disable_Copy_And_Assign(MyWalker);
    };

}

#include "y/stream/libc/output.hpp"

Y_UTEST(parser)
{
    MyParser parser;
    Jive::Syntax::Rule::Verbose = Environment::Flag("VERBOSE");
    MyWalker  analyze(parser);

    if(argc>1)
    {
        AutoPtr<Jive::XNode> tree;
        {
            Jive::Source source( Jive::Module::OpenFile(argv[1]) );
            tree = parser.parse(source);
            Y_ASSERT(tree.isValid());
            Vizible::Render("json-tree.dot",*tree);
            analyze( & *tree );
        }

        {
            OutputFile fp("json-tree.bin");
            const size_t nw = tree->serialize(fp);
            std::cerr << "written: " << nw << std::endl;
        }

        {
            std::cerr << "Reloading..." << std::endl;
            Jive::Source         source( Jive::Module::OpenFile("json-tree.bin") );
            AutoPtr<Jive::XNode> reloaded = Jive::XNode::Load(source,parser);

            Y_CHECK( *reloaded == *tree );

        }
    }

}
Y_UDONE()
