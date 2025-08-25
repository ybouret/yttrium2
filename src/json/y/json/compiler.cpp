
#include "y/json/compiler.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"

#include "y/container/algorithm/reverse.hpp"

#include "y/jive/parser.hpp"
#include "y/jive/analyzer.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{

    namespace JSON
    {

#define Y_JSON_Push(ID) Y_Jive_Push(Code,ID)
#define Y_JSON_Func(ID) Y_Jive_Func(Code,ID)

        class Compiler:: Code : public Jive::Parser, public Jive::Analyzer
        {
        public:

            inline virtual ~Code() noexcept {}

            inline explicit Code() :
            Jive::Parser("JSON"),
            Jive::Analyzer( static_cast<Grammar &>(*this) ),
            values(),
            pairs()
            {
                //verbose = true;

                //--------------------------------------------------------------
                //
                //
                // setup parser
                //
                //
                //--------------------------------------------------------------
                Alt &       JSON    = alt(lang);
                Alt &       Value   = alt("Value");
                const Rule &STRING  = plugin(Jive::Lexical::JString::Class, "String");
                const Rule &NUMBER  = term("Number","[-+]?[:digit:]+([.][:digit:]+)?([eEdD][-+]?[:digit:]+)?");

                {
                    Alt & ARRAY = alt("Array");
                    ARRAY << heavyList("HeavyArray", '[', Value, ',', ']');
                    ARRAY << emptyList("EmptyArray", '[', ']');
                    JSON  << ARRAY;
                    Value << ARRAY;
                }

                {
                    Alt & OBJECT = alt("Object");
                    {
                        const Rule & PAIR = ( agg("Pair") << STRING << ':' << Value );
                        OBJECT << ( agg("HeavyObject") << '{' << PAIR << extra(',',PAIR) << '}' );
                    }
                    OBJECT << emptyList("EmptyObject", '{', '}');
                    JSON  << OBJECT;
                    Value << OBJECT;
                }

                Value << STRING << NUMBER << "null" << "true" << "false";

                //--------------------------------------------------------------
                //
                //
                // setup lexer
                //
                //
                //--------------------------------------------------------------
                drop("[:blank:]");
                endl("[:endl:]",false);

                render();
                validate();

                //--------------------------------------------------------------
                //
                //
                // setup analyzer
                //
                //
                //--------------------------------------------------------------
                Y_JSON_Push(Number);
                Y_JSON_Push(null);
                Y_JSON_Push(true);
                Y_JSON_Push(false);
                Y_JSON_Push(String);

                Y_JSON_Func(EmptyArray);
                Y_JSON_Func(EmptyObject);
                Y_JSON_Func(Pair);
                Y_JSON_Func(HeavyArray);
                Y_JSON_Func(HeavyObject);


            }

            Value & compile(Jive::Source &source)
            {
                AutoPtr<XNode> tree = parse(source); assert( tree.isValid() );
                if(verbose) Vizible::Render("jtree.dot", *tree);
                walk( & *tree );
                return values.head();
            }



        private:
            Y_Disable_Copy_And_Assign(Code);

            Array              values;
            Vector<SharedPair> pairs;

            inline virtual void init()
            {
                values.free();
                pairs.free();
            }

            inline virtual void quit()
            {
                //std::cerr << "result:" << values << std::endl;
                if(values.size()!=1)
                    throw Specific::Exception(lang->c_str(),"corrupted syntax tree");
            }

            inline void onNumber(const Token &token)
            {
                const String s = token.toString();
                const Number n = ASCII::Convert::To<Number>(s,"Number");
                Value        v(n); assert(v.type == IsNumber);
                values.add(v);
            }

            inline void onnull(const Token &)
            {
                Value nil;
                values.add(nil);
            }

            inline void ontrue(const Token &)
            {
                Value _(true);
                values.add(_);
            }

            inline void onfalse(const Token &)
            {
                Value _(false);
                values.add(_);
            }

            inline void onString(const Token &token)
            {
                const String s = token.toString(1,1);
                Value _(s);
                values.add(_);
            }

            inline void onEmptyArray(const size_t)
            {
                Value _(AsArray);
                values.add(_);
            }


            inline void onEmptyObject(const size_t)
            {
                Value _(AsObject);
                values.add(_);
            }

            void onPair(const size_t)
            {
                assert(values.size()>=2);

                // get value at top
                Value v; v.xch( values.tail() ); values.popTail();

                // get string at top
                assert(values.tail().type == IsString);
                SharedPair pair = new Pair( values.tail().as<String>() ); values.popTail();

                pair->v.xch(v);

                pairs << pair;
                //std::cerr << "pairs=" << pairs << std::endl;
            }


            void onHeavyArray(size_t n)
            {
                //std::cerr << "values=" << values << " / n=" << n << std::endl;
                assert(values.size()>=n);
                Value   val(AsArray);
                {
                    Array & arr = val.as<Array>();
                    while(n-- > 0) { arr.add( values.tail() ); values.popTail(); }
                    Algorithm::Reverse(arr,Memory::Stealth::Swap<Value>);
                }
                values.add(val);
            }

            void onHeavyObject(size_t n)
            {
                assert(pairs.size()>=n);
                Value val(AsObject);
                {
                    JSON::Object &obj = val.as<JSON::Object>();
                    while(n-- > 0)
                    {
                        if(!obj.insert( pairs.tail() )) throw Specific::Exception(lang->c_str(),"multiple keys in Object");
                        pairs.popTail();
                    }
                    obj.reverse();
                }
                values.add(val);
            }
        };

        Compiler:: Compiler() : code( new Code() ), verbose(code->verbose)
        {

        }


        Compiler:: ~Compiler() noexcept
        {
            assert(code);
            Destroy(code);
        }

        void Compiler:: operator()( Value &value, Jive::Source &source )
        {
            value.nullify();
            value.xch( code->compile(source) );
        }

    }

}

