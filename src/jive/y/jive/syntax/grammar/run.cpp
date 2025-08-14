
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
                const Rule * self = rules.head; if(!self) throw Specific::Exception(lang->c_str(),"no rules");
                Node *       root = 0;
                return self->accepts(root,lexer,source) ? onSuccess(root, lexer, source) : onFailure(lexer,source);
            }


            Node * Grammar:: onSuccess(Node * const root, Lexer &lexer, Source &source)
            {
                AutoPtr<Node> guard(root);
                AutoPtr<Lexeme> lx = lexer.query(source);
                if(lx.isValid())
                {
                    throw Specific::Exception(lang->c_str(),"extraneous '%s'", lx->name->c_str());
                }

                return guard.yield();
            }

            Node * Grammar:: onFailure(Lexer &lexer, Source &source)
            {
                throw Specific::Exception(lang->c_str(),"failure");
            }
        }

    }

}

