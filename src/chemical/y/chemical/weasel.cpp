
#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/weasel/formula/translator.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/chemical/equilibrium.hpp"



namespace Yttrium
{
    namespace Chemical
    {
        const char * const Weasel::CallSign = "Weasel";

        const char * const Weasel::Coef     = "Coef";
        const char * const Weasel::RegExp   = "RegExp";
        const char * const Weasel::StringID = "String";


        namespace
        {
            class WeaselCode : public Weasel::Parser
            {
            public:
                inline WeaselCode() :
                Weasel::Parser(),
                translator(*this)
                {

                }

                inline ~WeaselCode()
                {

                }

                Weasel::FormulaTranslator translator;

            private:
                Y_Disable_Copy_And_Assign(WeaselCode);
            };


            static void *       WeaselImpl[ Alignment::WordsFor<WeaselCode>::Count ];
            static WeaselCode * code = 0;
        }

        Weasel:: ~Weasel() noexcept
        {
            assert(0!=code);
            Destruct(code);
            code = 0 ;
            Y_Memory_BZero(WeaselImpl);
        }

        Weasel:: Weasel()
        {
            assert(0==code);
            try {
                code = new ( Y_Memory_BZero(WeaselImpl) ) WeaselCode();
            }
            catch(...) { code = 0; throw; }
        }


        void Weasel:: display(std::ostream &os, size_t indent) const
        {
            init(os,indent);

            quit(os,indent);
        }


        namespace
        {
            static inline
            void   cleanActors(XNode * const node) noexcept
            {
                assert(node);
                assert(node->isInternal());
                XTree * const tree = dynamic_cast<XTree *>(node);
                Jive::Syntax::NodeList temp;
                while(tree->size)
                {
                    XNode * const sub = tree->popHead();
                    if( '+' == sub->name() ) { delete sub; continue; }
                    temp.pushTail(sub);
                }
                tree->steal(temp);
            }
            
            static inline
            void cleanEquilibrium(XNode * const node) noexcept
            {
                assert(node);
                assert(node->defines<Equilibrium>());
                XTree * const tree = dynamic_cast<XTree *>(node);
                XNode * sub  = tree->head; assert(sub); assert("EID"==sub->name());
                sub          = sub->next;  assert(sub); assert(Equilibrium::Prod==sub->name()); cleanActors(sub);
                sub          = sub->next;  assert(sub); assert(Equilibrium::Reac==sub->name()); cleanActors(sub);
            }
        }

        XNode * Weasel:: parse( Jive::Module *m )
        {
            Jive::Source   source(m);
            AutoPtr<XNode> node = code->parse(source);
            assert(node.isValid());
            assert(node->defines<Weasel>());

            for(XNode *sub = dynamic_cast<const XTree&>(*node).head;sub;sub=sub->next)
            {
                if(sub->defines<Equilibrium>()) {
                    cleanEquilibrium(sub); continue;
                }
            }

            return node.yield();
        }

        String  Weasel:: formulaToText(const Formula &f, int * const z)
        {
            return code->translator.decode(f,z,false);
        }

        String  Weasel:: formulaToHTML(const Formula &f)
        {
            return code->translator.decode(f,0,true);
        }

        XNode * Weasel:: formula1(Jive::Module *m)
        {
            static const char fn[] = "Weasel::formula1";
            Jive::Source   source(m);
            AutoPtr<XNode> node = code->parse(source);
            assert(node.isValid());
            assert(node->defines<Weasel>());
            XTree &tree = dynamic_cast<XTree&>(*node);
            if(tree.size!=1)                    throw Specific::Exception(fn,"need exactly one formula in '%s'", m->tag->c_str());
            if(!tree.head->defines<Formula>())  throw Specific::Exception(fn,"bad '%s'", tree.head->name().c_str());
            return tree.popHead();
        }


    }
}
