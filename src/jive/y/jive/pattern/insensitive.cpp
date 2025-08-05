
#include "y/jive/pattern/posix.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace
        {
            static inline Pattern * IgnByte( Byte * const p )
            {
                AutoPtr<Pattern> motif = p;

                const uint8_t c = p->code;

                if( islower(c) )
                {
                    AutoPtr<Logic> q = new Or();
                    q->pushTail( motif.yield() );
                    q->pushTail( new Byte( toupper(c)) );
                    return q.yield();
                }

                if( isupper(c) )
                {
                    AutoPtr<Logic> q = new Or();
                    q->pushTail( new Byte( tolower(c)) );
                    q->pushTail( motif.yield() );
                    return q.yield();
                }

                return motif.yield();
            }

            static inline void FillLogic(const uint8_t a, const uint8_t b, void * const args)
            {
                assert(args);
                static_cast<Logic *>(args)->add(a,b);
            }

            static inline Pattern * IgnLump( Lump * const p )
            {
                AutoPtr<Pattern> motif = p;

                FirstChars fc;
                const int  top     = int(p->upper);
                bool       changed = false;
                for(int c = int(p->lower);c<=top;++c)
                {
                    fc.add(c);
                    if( islower(c) ) { changed=true; fc.add(toupper(c)); }
                    if( isupper(c) ) { changed=true; fc.add(tolower(c)); }
                }

                if(changed)
                {
                    AutoPtr<Logic> q = new Or();
                    fc.run(FillLogic,& *q);
                    return q.yield();
                }

                return motif.yield();
            }


            static inline Pattern * IgnNot( Not * const p )
            {
                AutoPtr<Pattern> motif = p;

                const uint8_t c = p->code;

                if( islower(c) )
                {
                    AutoPtr<Logic> q = new None();
                    q->pushTail( motif.yield() );
                    q->pushTail( new Byte( toupper(c)) );
                    return q.yield();
                }

                if( isupper(c) )
                {
                    AutoPtr<Logic> q = new None();
                    q->pushTail( new Byte( tolower(c)) );
                    q->pushTail( motif.yield() );
                    return q.yield();
                }

                return motif.yield();
            }

            static inline
            Pattern * IgnLogic(Logic * const p)
            {
                AutoPtr<Pattern> motif = p;

                {
                    Patterns plist;
                    while(p->size>0)
                    {
                        plist.pushTail( Pattern::Insensitive(p->popHead()) );
                    }
                    p->swapListFor(plist);
                }

                return motif.yield();
            }

            Pattern * IgnJoker(Joker * const p)
            {
                AutoPtr<Pattern> guard = p;

                {
                    Motif tmp = Pattern::Insensitive( p->motif->clone() );
                    tmp.xch( Coerce(p->motif) );
                }

                return guard.yield();

            }
        }

        Pattern * Pattern:: Insensitive(Pattern * const p)
        {
            AutoPtr<Pattern> motif = p;

            switch(p->uuid)
            {
                case Byte::UUID: return IgnByte( motif.yield()->as<Byte>() );
                case Lump::UUID: return IgnLump( motif.yield()->as<Lump>() );
                case Not::UUID:  return IgnNot(  motif.yield()->as<Not>() );

                case And::  UUID: return IgnLogic( motif.yield()->as<And>() );
                case Or::   UUID: return IgnLogic( motif.yield()->as<Or>() );
                case None:: UUID: return IgnLogic( motif.yield()->as<None>() );

                case Option:: UUID: return IgnJoker( motif.yield()->as<Option>() );
                case Repeat:: UUID: return IgnJoker( motif.yield()->as<Repeat>() );
                case Amount:: UUID: return IgnJoker( motif.yield()->as<Amount>() );

            }

            return motif.yield();
        }
    }

}
