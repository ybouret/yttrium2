#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"

#include "y/jive/lexical/plugin/jstring.hpp"

#include "y/string/env.hpp"

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


            Render("json-grammar.dot",*this);

        }

        virtual ~MyParser() noexcept
        {

        }
    private:
        Y_Disable_Copy_And_Assign(MyParser);
    };
}

Y_UTEST(parser)
{
    MyParser parser;
    Jive::Syntax::Rule::Verbose = Environment::Flag("VERBOSE");
    
    if(argc>1)
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        AutoPtr<Jive::XNode> tree = parser.parse(source);
        Y_ASSERT(tree.isValid());
        Vizible::Render("json.dot",*tree);
    }

}
Y_UDONE()
