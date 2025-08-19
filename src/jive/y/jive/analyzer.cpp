

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

            inline explicit Code() : verbose(true)
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
                Y_Print("[push] " << *node->lexeme);
            }

            void on(const Syntax::InternalNode * const node, size_t depth)
            {
                assert(0!=node);
                ++depth;
                for(const XNode *sub = node->head; sub; sub=sub->next)
                     walk(sub,depth);
                --depth;
                Y_Print("[call] " << node->name() << "/" << node->size);
            }

            SuffixMap<String,TerminalProc> tdb;
            SuffixMap<String,InternalProc> idb;


            bool verbose;
        private:
            Y_Disable_Copy_And_Assign(Code);
        };


        Analyzer:: Analyzer(const Syntax::Grammar &G, const bool verbose) :
        lang(G.lang),
        code( new Code() )
        {
            code->verbose = verbose;
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

