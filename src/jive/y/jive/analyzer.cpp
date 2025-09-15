

#include "y/jive/analyzer.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/node/terminal.hpp"
#include "y/container/associative/suffix/map.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

#define Y_Print(MSG) do { if(verbose) { Prefix(std::cerr,depth) << MSG << std::endl; } } while(false)

        class Analyzer :: Code : public Object
        {
        public:

            inline explicit Code(const Tag     &  l,
                                 const Analysis   a,
                                 const Analyzer  &A) :
            tdb(),
            idb(),
            lang(l),
            kind(a),
            analyzer(A),
            verbose(false)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

            static std::ostream & Prefix(std::ostream &os, const size_t depth)
            {
                os << "|_";
                Core::Indent(os,depth<<1,'_');
                return os;
            }

            void walk(const XNode * const node,
                      const size_t        depth)
            {
                assert(0!=node);

                switch(node->type)
                {
                    case Syntax::IsTerminal: return on(  dynamic_cast<const Syntax::TerminalNode *>(node),depth);
                    case Syntax::IsInternal: return on(  dynamic_cast<const Syntax::InternalNode *>(node),depth);
                }
            }

            void on(const Syntax::TerminalNode * const node, const size_t depth)
            {
                assert(0!=node);
                const Lexeme & lexeme = *node->lexeme;
                Y_Print("[push] " << lexeme);
                const String &       name = *lexeme.name;
                TerminalProc * const hook = tdb.search(name);
                if(hook)
                {
                    (*hook)(lexeme);
                    analyzer.show(depth);
                }
                else
                {
                    if(Exhaustive==kind) throw Specific::Exception(lang->c_str(),"can't analyze terminal %s", name.c_str());
                }
            }

            void on(const Syntax::InternalNode * const node, size_t depth)
            {
                assert(0!=node);
                ++depth;
                for(const XNode *sub = node->head; sub; sub=sub->next)
                     walk(sub,depth);
                --depth;
                Y_Print("[call] " << node->name() << "/" << node->size);
                const String &       name = node->name();
                InternalProc * const hook = idb.search(name);
                if(hook)
                {
                    (*hook)(node->size);
                    analyzer.show(depth);
                }
                else
                {
                    if(Exhaustive==kind) throw Specific::Exception(lang->c_str(),"can't analyze internal %s", name.c_str());
                }
            }

            SuffixMap<String,TerminalProc> tdb;
            SuffixMap<String,InternalProc> idb;

            const Tag       lang;
            const Analysis  kind;
            const Analyzer &analyzer;
            bool            verbose;
        private:
            Y_Disable_Copy_And_Assign(Code);
        };

#if defined(_MSC_VER)
#pragma warning ( disable : 4355 )
#endif
        Analyzer:: Analyzer(const Syntax::Grammar &G,
                            const Analysis         a) :
        grammar(G),
        code( new Code(grammar.lang,a,*this) ),
        verbose(code->verbose)
        {
        }

        Analyzer:: ~Analyzer() noexcept
        {
            Destroy(code);
        }


        void Analyzer:: walk(const XNode * const root)
        {
            assert(code);
            init();
            code->walk(root,0);
            quit();
        }

        void Analyzer:: on(const Tag &id, const TerminalProc &proc)
        {
            const Syntax::Rule * const rule = grammar.queryRule(id);
            if(!rule)
                throw Specific::Exception(grammar.lang->c_str(),"no rule '%s' to analyze", id->c_str());

            if(!rule->isTerminal())
                throw Specific::Exception(grammar.lang->c_str(),"rule '%s' is not a terminal", id->c_str());

            if( !code->tdb.insert(*id,proc) )
                throw Specific::Exception(grammar.lang->c_str(),"multiple analysis of terminal '%s'", id->c_str());
        }

        void Analyzer:: on(const Tag &id, const InternalProc &proc)
        {
            const Syntax::Rule * const rule = grammar.queryRule(id);

            if(!rule)
                throw Specific::Exception(grammar.lang->c_str(),"no rule '%s' to analyze", id->c_str());

            if(Syntax::Aggregate::UUID != rule->uuid)
                throw Specific::Exception(grammar.lang->c_str(),"rule '%s' is not an aggregate", id->c_str());

            if( !code->idb.insert(*id,proc) )
                throw Specific::Exception(grammar.lang->c_str(),"multiple analysis of aggregate '%s'", id->c_str());
        }


        void Analyzer:: show(const size_t) const
        {

        }

        Walker:: Walker(const Syntax::Grammar &G) :
        Analyzer(G,Permissive)
        {
            verbose = true;
        }

        Walker:: ~Walker() noexcept
        {
        }

        void Walker:: init()
        {
            if(verbose) std::cerr << grammar.lang << " Analyzer init" << std::endl;
        }

        void Walker:: quit()
        {
            if(verbose) std::cerr << grammar.lang << " Analyzer quit" << std::endl;
        }
    }

}

