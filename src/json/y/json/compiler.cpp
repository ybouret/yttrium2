
#include "y/json/compiler.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"

namespace Yttrium
{

    namespace JSON
    {

        Compiler:: ~Compiler() noexcept
        {
        }

        Compiler:: Compiler() : Jive::Parser("JSON")
        {
            drop("[:blank:]");
            endl("[:endl:]",false);

            Alt &       JSON    = alt(lang);
            Alt &       Value   = alt("Value");
            const Rule &STRING  = plugin(Jive::Lexical::JString::Class, "String");
            const Rule &NUMBER  = term("Number","[:digit:]+");

            {
                Alt & ARRAY = alt("Array");
                ARRAY << ( agg("HeavyArray") << '[' << Value << extra(',', Value) << ']');
                ARRAY << ( agg("EmptyArray") << '[' << ']');
                JSON  << ARRAY;
                Value << ARRAY;
            }

            {
                Alt & OBJECT = alt("Object");
                {
                    const Rule & PAIR = ( agg("Pair") << STRING << ':' << Value );
                    OBJECT << ( agg("HeavyObject") << '{' << PAIR << extra(',',PAIR) << '}' );
                }
                OBJECT << ( agg("EmptyObject") << '{' << '}');
                JSON  << OBJECT;
                Value << OBJECT;
            }

            Value << STRING << NUMBER << "null" << "true" << "false";

            render();

        }
    }

}

