
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


        namespace {

            static inline void Fill(const uint8_t a, const uint8_t b, void * args)
            {
                assert(args);
                Logic * const p = (Logic *)args;
                p->add(a,b);
            }

        }

        Pattern * Pattern:: Among(const String &data)
        {
            FirstChars fc;
            for(size_t i=data.size();i>0;--i)
                fc.add( data[i] );

            Logic * const p = new Or();
            AutoPtr<Pattern> motif = p;
            fc.run(Fill,p);
            return  motif.yield();

        }

        Pattern * Pattern:: Among(const char * const data)
        {
            const String _(data);
            return Among(_);
        }


        Pattern * Pattern:: Exact(const String &data)
        {
            AutoPtr<Logic> p = new And();
            for(size_t i=1;i<=data.size();++i) p->pushHead( new Byte(data[i]) );
            return p.yield();
        }

        Pattern * Pattern:: Exact(const char * const data)
        {
            const String _(data);
            return Exact(_);
        }



    }

}


