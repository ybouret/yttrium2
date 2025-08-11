
#include "y/jive/pattern/posix.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"


namespace Yttrium
{
    namespace Jive
    {

        bool Pattern:: isBasic()  const noexcept
        {
            switch(uuid)
            {
                case Byte::UUID:
                case Lump::UUID:
                case Not:: UUID:
                    return true;
                default:
                    break;
            }
            return false;
        }

        namespace
        {

            // fill list with matching Byte/Lump
            static inline
            void FillList(const uint8_t a, const uint8_t b, void * const args)
            {
                assert(args);
                Patterns &plist = *(Patterns *)args;
                if(a==b)
                    plist.pushTail( new Byte(a) );
                else
                    plist.pushTail( new Lump(a,b) );
            }

            // basic => use first char to get equivalent
            static inline
            void OptimizeOrList(Patterns &plist)
            {
                FirstChars fc;
                Patterns   xlist;
                while(plist.size)
                {
                    Pattern * const p = plist.popHead();
                    if(p->isBasic())
                    {
                        fc += p->firstChars();
                        delete p;
                    }
                    else
                    {
                        xlist.pushTail(p);
                    }
                }
                fc.run(FillList,&plist);
                plist.mergeTail(xlist);
            }

            static inline
            Pattern * OptimizeLogic(And * const p)
            {
                assert(p);
                AutoPtr<Pattern> motif(p);
                {
                    Patterns         plist;
                    while(p->size)
                    {
                        Pattern * op =  Pattern::Optimize(p->popHead());

                        // merge nested same
                        if(op->uuid == And::UUID)
                        {
                            plist.mergeTail( *op->as<And>() );
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

            static inline
            Pattern * OptimizeLogic(Or * const p)
            {
                assert(p);
                AutoPtr<Pattern> motif(p);
                {
                    Patterns         plist;
                    while(p->size)
                    {
                        Pattern * op =  Pattern::Optimize(p->popHead());

                        // merge nested same
                        if(op->uuid == Or::UUID)
                        {
                            plist.mergeTail( *op->as<Or>() );
                            delete op;
                            continue;
                        }

                        // grow plist
                        plist.pushTail(op);
                    }
                    p->swapListFor(plist);
                }

                // specific optimization
                OptimizeOrList(*p);

                if(1==p->size) return p->popHead();
                return motif.yield();
            }

            static inline
            Pattern * OptimizeLogic(None * const p)
            {
                assert(p);
                AutoPtr<Pattern> motif(p);
                {
                    Patterns         plist;
                    while(p->size)
                    {
                        Pattern * op =  Pattern::Optimize(p->popHead());
                        plist.pushTail(op);
                    }
                    p->swapListFor(plist);
                }

                
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
                case Lump::UUID: {
                    const Lump * const q = p->as<Lump>();
                    if(q->lower == q->upper) return new Byte(q->lower);
                } break;

                case And::  UUID: return OptimizeLogic( motif.yield()->as<And>() );
                case Or::   UUID: return OptimizeLogic( motif.yield()->as<Or>() );
                case None:: UUID: return OptimizeLogic( motif.yield()->as<None>() );

                case Option::UUID: return OptimizeJoker( motif.yield()->as<Option>() );
                case Repeat::UUID: return OptimizeJoker( motif.yield()->as<Repeat>() );
                case Amount::UUID: return OptimizeJoker( motif.yield()->as<Amount>() );

                default:
                    break;
            }


            return motif.yield();
        }


        namespace {

            static inline void FillLogic(const uint8_t a, const uint8_t b, void * args)
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
                fc.add( (uint8_t)data[i] );

            Logic * const p = new Or();
            AutoPtr<Pattern> motif = p;
            fc.run(FillLogic,p);
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
            for(size_t i=1;i<=data.size();++i) p->pushHead( new Byte( (uint8_t)data[i]) );
            return p.yield();
        }

        Pattern * Pattern:: Exact(const char * const data)
        {
            const String _(data);
            return Exact(_);
        }



    }

}


