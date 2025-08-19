
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/node/terminal.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            Terminal:: ~Terminal() noexcept
            {
                
            }


            bool Terminal:: accepts(Node * &tree, Lexer &lexer, Source &source, size_t depth) const
            {
                Lexeme * const lx = lexer.query(source);
                if(0==lx)
                {
                    Y_Jive_XRule("[EOF]@" << name);
                    return false;
                }

                if(  (*lx->name != *name) )
                {
                    lexer.store(lx);
                    return false;
                }

                Y_Jive_XRule("accept " << *lx);
                Node::Grow(tree, Node::Make(*this,lx) );
                return true;
            }

            OutputStream & Terminal:: vizDecl(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=box";
                return Endl(fp<<']');
            }

            OutputStream & Terminal:: vizPost(OutputStream &fp) const
            {
                return fp;
            }


        }

    }

}


