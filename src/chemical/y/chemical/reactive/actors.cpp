
#include "y/chemical/reactive/actors.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Actors:: CallSign = "Actors";

        Actors:: ~Actors() noexcept
        {
        }

        Actors:: Actors( const Actor::Role r) :
        list(),
        role(r)
        {
        }

        Actors:: Actors(const Actors &a) :
        Entity(a.name),
        Ingress<const Actor::CoreList>(),
        Freezable(),
        list(a.list),
        role(a.role)
        {
        }

        bool Actors:: got(const Species &sp) const noexcept
        {
            for(const Actor *a=list.head;a;a=a->next)
            {
                if( & a->sp == &sp ) return true;
                assert(a->sp.name != sp.name );
            }

            return false;
        }

        bool Actors:: gotOneOf(const SList &slist) const noexcept
        {
            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                if(got(**sn)) return true;
            }
            return false;
        }



        void Actors:: add(const unsigned nu, const Species &sp)
        {
            static const char * const sep[2] = { " + ", "+" };
            // sanity
            assert(nu>0);
            assert(!got(sp));

            checkpoint(name,"add");

            // new actor
            const Actor &last = *list.pushTail( new Actor(nu,sp,role) );

            // new name
            try
            {
                String newName = name;
                if(1==list.size)
                    newName = last.name;
                else
                    newName += (sep[role] + last.name);
                Coerce(name).swapFor(newName);
                enroll(last);
            }
            catch(...)
            {
                delete list.popTail();
                throw;
            }
        }

        void Actors:: add(const Species &sp)
        {
            add(1,sp);
        }



        Y_Ingress_Impl(Actors,list)

        void Actors:: massAction(XMul &X, const XReadable &C, const Level L) const
        {
            for(const Actor *a=list.head;a;a=a->next) a->massAction(X,C,L);
        }

        void Actors:: massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            for(const Actor *a=list.head;a;a=a->next) a->massAction(X,C,L,xi);
        }

        xreal_t Actors:: fastLimit(const XReadable &C, const Level L) const noexcept
        {
            assert(list.size>0);
            const Actor * a  = list.head;
            xreal_t       xi = a->sp(C,L) / a->xn; assert(xi>=a->zero);

            for(a=a->next;a;a=a->next) {
                InSituMin(xi, a->sp(C,L) / a->xn); assert(xi>=a->zero);
            }
            
            return xi;
        }


        void Actors:: moveSafely(XWritable &C, const Level L, const xreal_t xi) const
        {
            for(const Actor *a=list.head;a;a=a->next) a->moveSafely(C,L,xi);
        }


        bool Actors:: degenerate(const XReadable &C, const Level L) const noexcept
        {

            for(const Actor *a=list.head;a;a=a->next)
            {
                if( a->sp(C,L) <= a->zero ) return true;
            }
            
            return false;
        }


        void Actors:: diffAction(XWritable       &dma,
                                 XMul            &X,
                                 const xreal_t    K,
                                 const XReadable &C,
                                 const Level      L,
                                 XWritable       &ma) const
        {
            // storing individual mass actions
            for(const Actor *a=list.head;a;a=a->next)
            {
                X.ld1();
                a->massAction(X,C,L);
                a->sp(ma,L) = X.product();
            }

            // computing derivative times K
            for(const Actor *a=list.head;a;a=a->next)
            {
                X = K;
                a->diffAction(X,C,L);
                for(const Actor *b=a->prev;b;b=b->prev) X << b->sp(ma,L);
                for(const Actor *b=a->next;b;b=b->next) X << b->sp(ma,L);
                a->sp(dma,L) = X.product();
            }

        }


        String Actors:: html() const
        {
            String res;
            const Actor *a = list.head;
            if(a)
            {
                res = a->html();
                for(a=a->next;a;a=a->next)
                {
                    res += '+';
                    res += a->html();
                }
            }
            return res;
        }
    }

}

