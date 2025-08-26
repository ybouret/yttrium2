
#include "y/chemical/weasel/equilibrium/translator.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/node/terminal.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        Weasel:: EquilibriumTranslator:: ~EquilibriumTranslator() noexcept
        {
        }

        Weasel:: EquilibriumTranslator:: EquilibriumTranslator(const Jive::Syntax::Grammar &G) :
        Jive::Analyzer(G,Jive::Permissive)
        {
            verbose = true;
        }

        

        Equilibrium * Weasel:: EquilibriumTranslator::decode(const XNode * const root,
                                                             Library           & lib,
                                                             const size_t        top,
                                                             Lua::VM           & lvm)
        {
            std::cerr << "Decoding Equilibrium" << std::endl;
            assert(root);
            assert(root->defines<Equilibrium>());
            const XTree * const tree = dynamic_cast<const XTree *>(root); assert(tree);
            const XNode *       node = tree->head; assert(node); assert(node->name() == "EID");
            const String        eid  = dynamic_cast<const XTerm*>(node)->lexeme->toString(1,0);
            std::cerr << "Using '" << eid << "'" << std::endl;

            // decoding reactants
            node = node->next; assert(node); assert(node->name() == Components::Reac);
            Actor::List reac;
            decode(eid,reac,node,lib);

            // decoding products
            node = node->next; assert(node); assert(node->name() == Components::Prod);
            Actor::List prod;
            decode(eid,prod,node,lib);

            node = node->next; assert(node); assert(node->name() == "KSTR" );

            AutoPtr<Equilibrium> eq = new ConstEquilibrium(eid,1.0,top);
            for(const Actor *a=reac.head;a;a=a->next) eq->r(a->nu,a->sp);
            for(const Actor *a=prod.head;a;a=a->next) eq->p(a->nu,a->sp);
            std::cerr << eq << std::endl;
        }

        void Weasel:: EquilibriumTranslator:: decode(const String &eid, Actor::List &list, const XNode * const root, Library &lib)
        {
            assert(root);
            assert(root->name() == Components::Reac || root->name() == Components::Prod);
            const String       &side = root->name();
            const XTree * const tree = dynamic_cast<const XTree *>(root);

            for(const XNode * node = tree->head; node; node=node->next)
            {
                const XTree * ac = dynamic_cast<const XTree *>(node); assert(ac);
                assert(1==ac->size || 2==ac->size);

                // extract species
                const Formula  formula( ac->tail->clone() );
                const Species &sp = lib[formula];
                std::cerr << "found " << sp << std::endl;

                // optional coefficient
                if(2==ac->size)
                {
                    assert( "Coef" == ac->head->name() );
                    unsigned  n = 0;
                    {
                        const apn nu = dynamic_cast<const XTerm*>(ac->head)->lexeme->toNatural();
                        if( nu.bits() <= 0 ) throw Specific::Exception(eid.c_str(),"zero coef for %s '%s",side.c_str(),sp.name.c_str());
                        if( !nu.tryCast(n) ) throw Specific::Exception(eid.c_str(),"overflow coef for %s '%s",side.c_str(),sp.name.c_str());
                    }
                    list.pushTail( new Actor(n,sp) );
                }
                else
                {
                    list.pushTail( new Actor(1,sp) );
                }
            }
        }



    }

}


