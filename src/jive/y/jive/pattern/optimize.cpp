
#include "y/jive/pattern/posix.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"


namespace Yttrium
{
    namespace Jive
    {

        namespace
        {


            template <typename LOGIC>
            static Pattern * OptimizeCommonLogic(LOGIC * const p)
            {
                assert(p);
                AutoPtr<Pattern> motif(p);
                {
                    Patterns         plist;
                    while(p->size)
                    {
                        Pattern * op =  Pattern::Optimize(p->popHead());

                        // merge nested same
                        if(op->uuid == LOGIC::UUID)
                        {
                            plist.mergeTail( *op->as<LOGIC>() );
                            delete op;
                            continue;
                        }

                        // grow plist
                        plist.pushTail(op);
                    }
                    p->swapListFor(plist);
                }

                if(1==p->size) return p->popHead();
                return motif.yield();
            }

            template <typename JOKER>
            inline Pattern * OptimizeJoker(JOKER * const p)
            {
                assert(p);
                AutoPtr<Pattern> guard(p);
                {
                    Motif tmp = Pattern::Optimize(p->motif->clone());
                    tmp.xch( Coerce(p->motif) );
                }
                return guard.yield();
            }



        }

        Pattern * Pattern:: Optimize(Pattern * const p)
        {
            AutoPtr<Pattern> motif(p);

            switch(p->uuid)
            {
                case And::UUID: return OptimizeCommonLogic( motif.yield()->as<And>() );
                case Or::UUID:  return OptimizeCommonLogic( motif.yield()->as<Or>() );

                case Option::UUID: return OptimizeJoker( motif.yield()->as<Option>() );
                case Repeat::UUID: return OptimizeJoker( motif.yield()->as<Repeat>() );
                case Amount::UUID: return OptimizeJoker( motif.yield()->as<Amount>() );

                default:
                    break;
            }


            return motif.yield();
        }
    }

}


