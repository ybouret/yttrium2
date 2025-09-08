
#include "y/jive/syntax/grammar.hpp"
#include "y/exception.hpp"
#include "y/jive/syntax/node/terminal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            Node * Grammar:: run(Lexer &lexer, Source &source)
            {
                const Rule * self = rules.head; if(!self) throw Specific::Exception(lang->c_str(),"no rules");
                Node *       root = 0;
                return self->accepts(root,lexer,source,0) ? onSuccess(root, lexer, source) : onFailure(lexer,source);
            }


            void Grammar:: sendTo(Exception &excp, const Lexeme &lx) const
            {
                const Tag &tag = lx.name;
                excp.add("'%s'",tag->c_str());
                if(const Rule * const rule = queryRule(tag))
                {
                    assert(rule->isTerminal());
                    if(!dynamic_cast<const Terminal *>(rule)->univocal)
                    {
                        const String s = lx.toString();
                        excp.add("='%s'", s.c_str());
                    }
                }
                else
                {
                    excp.add(" (unmatched!)");
                }
            }

            Node * Grammar:: onSuccess(Node * const root, Lexer &lexer, Source &source)
            {
                if(!root) throw Specific::Exception(lang->c_str(), "*** NULL root from '%s'", source.context().tag->c_str());
                AutoPtr<Node> guard(root);
                AutoPtr<Lexeme> lx = lexer.query(source);

                if(lx.isValid())
                {
                    Specific::Exception excp(lang->c_str(),"extraneous ");
                    lx->stamp(excp);
                    sendTo(excp,*lx);
                    if(const TerminalNode * const last = root->lastTerm())
                    {
                        excp.add(" after ");
                        sendTo(excp, *last->lexeme);
                    }
                    throw excp;
                }
                if(Syntax::Rule::Verbose) {
                    std::cerr << "--> Building " << lang << " AST..." << std::endl;
                }
                return AST( guard.yield() );
            }

            Node * Grammar:: onFailure(Lexer &lexer, Source &source)
            {
                Specific::Exception excp(lang->c_str()," ");
                Lexemes &io = lexer.lxms;

                if(!io.tail) {
                    excp.add("empty input is not allowed");
                    throw excp;
                }

                AutoPtr<Lexeme> curr = io.popTail();
                AutoPtr<Lexeme> prev; if(io.tail) prev = io.popTail();
                io.release();
                AutoPtr<Lexeme> next = lexer.query(source);

                //std::cerr << "prev = " << prev << std::endl;
                //std::cerr << "curr = " << curr << std::endl;
                //std::cerr << "next = " << next << std::endl;

                curr->stamp(excp);
                excp.add("unexpected/unfinished ");
                sendTo(excp,*curr);
                if(prev.isValid())
                {
                    excp.add(" after ");
                    sendTo(excp,*prev);
                }


                throw excp;

            }
        }

    }

}

