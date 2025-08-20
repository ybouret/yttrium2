
#include "y/jive/syntax/grammar.hpp"
#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {

            static inline Node * LoadTerminal(const Rule * const rule,
                                              Source &           source,
                                              const Grammar &    G)
            {
                assert(rule);
                assert(rule->isTerminal());
                
                const Terminal * const term = dynamic_cast<const Terminal *>(rule); assert(term);
                AutoPtr<TerminalNode>  node = Node::Make( *term, new Lexeme(rule->name,source.context() ) );
                const char * const     rvar = rule->name->c_str();
                const size_t           n    = source.readVBR<size_t>(rvar,"size");
                for(size_t i=1;i<=n;++i)
                {
                    Char * const ch = source.get();
                    if(!ch) throw Specific::Exception(G.lang->c_str(),"missing data for '%s'",rvar);
                    node->lexeme->pushTail(ch);
                }
                return node.yield();
            }


            static inline Node * LoadInternal(const Rule * const rule,
                                              Source &           source,
                                              const Grammar     &G)
            {
                assert(rule);
                assert(rule->isInternal());

                const Internal * const intr = dynamic_cast<const Internal *>(rule); assert(intr);
                AutoPtr<InternalNode>  node = Node::Make( *intr );
                const char * const     rvar = rule->name->c_str();
                const size_t           n    = source.readVBR<size_t>(rvar,"size");
                for(size_t i=1;i<=n;++i) node->pushTail( Node::Load(source,G) );
                return node.yield();
            }


            Node * Node::Load(Source &source, const Grammar &G)
            {
                //--------------------------------------------------------------
                //
                // read identifier
                //
                //--------------------------------------------------------------
                const String       rid(source,"Jive::Node.name");


                // find matching rule
                const Rule * const rule = G.queryRule(rid);
                if(!rule)
                    throw Specific::Exception(G.lang->c_str(),"no rule '%s' to load from", rid.c_str());

                // process according to rule
                switch(rule->type)
                {
                    case IsTerminal: return LoadTerminal(rule,source,G);
                    case IsInternal: return LoadInternal(rule,source,G);
                }

                // never get here
                throw Specific::Exception(G.lang->c_str(),"invalid rule type");
                return 0;
            }

        }

    }

}


