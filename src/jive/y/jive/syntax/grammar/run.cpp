
#include "y/jive/syntax/grammar.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            Node * Grammar::run(Lexer &lexer, Source &source)
            {
                if(rules.size<=0) throw Specific::Exception(name->c_str(),"no rule");
                Node * root = 0;
                return rules.head->accepts(root,lexer,source) ? onSuccess(root, lexer, source) : onFailure(lexer,source);
            }


            Node * Grammar:: onSuccess(Node * const root, Lexer &lexer, Source &source)
            {
                AutoPtr<Node> guard(root);
                AutoPtr<Lexeme> lx = lexer.query(source);
                if(lx.isValid())
                {
                    throw Specific::Exception(name->c_str(),"extraneous '%s'", lx->name->c_str());
                }

                return guard.yield();
            }

            Node * Grammar:: onFailure(Lexer &lexer, Source &source)
            {
                throw Specific::Exception(name->c_str(),"failure");
            }
        }

    }

}

