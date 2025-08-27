
#include "y/chemical/reactive/actors.hpp"


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
        list(a.list),
        role(a.role)
        {
        }

        bool Actors:: has(const Species &sp) const noexcept
        {
            for(const Actor *a=list.head;a;a=a->next)
            {
                if( & a->sp == &sp ) return true;
                assert(a->sp.name != sp.name );
            }

            return false;
        }


        void Actors:: add(const unsigned nu, const Species &sp)
        {
            static const char * const sep[2] = { " + ", "+" };
            // sanity
            assert(nu>0);
            assert(!has(sp));


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
        
    }

}

