

#include "y/jive/analyzer.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/node/terminal.hpp"
#include "y/container/associative/suffix/map.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

#define Y_Print(MSG) do { if(verbose) { Prefix(std::cerr,depth) << MSG << std::endl; } } while(false)

        class Analyzer :: Code : public Object
        {
        public:

            inline explicit Code(const Tag     &l,
                                 const Analysis a) :
            tdb(),
            idb(),
            lang(l),
            kind(a),
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

            void walk(const XNode * const node, const size_t depth)
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
                }
                else
                {
                    if(Exhaustive==kind) throw Specific::Exception(lang->c_str(),"can't analyze internal %s", name.c_str());
                }
            }

            SuffixMap<String,TerminalProc> tdb;
            SuffixMap<String,InternalProc> idb;

            const Tag      lang;
            const Analysis kind;
            bool           verbose;
        private:
            Y_Disable_Copy_And_Assign(Code);
        };


        Analyzer:: Analyzer(const Syntax::Grammar &G,
                            const Analysis         a,
                            const bool             v ) :
        lang(G.lang),
        code( new Code(lang,a) )
        {
            code->verbose = v;
        }

        Analyzer:: ~Analyzer() noexcept
        {
            Destroy(code);
        }

        void Analyzer:: operator()(const XNode * const root)
        {
            assert(code);
            init();
            code->walk(root,0);
            quit();
        }

        void Analyzer:: on(const Tag &id, const TerminalProc &proc)
        {
            if( !code->tdb.insert(*id,proc) )
                throw Specific::Exception(lang->c_str(),"multiple analysis of terminal '%s'", id->c_str());
        }

        void Analyzer:: on(const Tag &id, const InternalProc &proc)
        {
            if( !code->idb.insert(*id,proc) )
                throw Specific::Exception(lang->c_str(),"multiple analysis of internal '%s'", id->c_str());
        }

        void Analyzer:: init()
        {
            if(code->verbose) std::cerr << lang << " Analyzer init" << std::endl;
        }

        void Analyzer:: quit()
        {
            if(code->verbose) std::cerr << lang << " Analyzer quit" << std::endl;
        }


    }

}

