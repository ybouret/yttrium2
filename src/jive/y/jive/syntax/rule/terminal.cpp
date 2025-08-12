
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/node/terminal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            Terminal:: ~Terminal() noexcept
            {
                
            }


            bool Terminal:: accepts(Node * &tree, Lexer &lexer, Source &source) const
            {
                Lexeme * const lx = lexer.query(source);
                if( (0==lx) || (*lx->name != *name) ) return false;
                Node::Grow(tree, Node::Make(*this,lx) );
                return true;
            }

        }

    }

}


