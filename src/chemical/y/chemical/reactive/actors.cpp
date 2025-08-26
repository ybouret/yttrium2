
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
        
        void Actors:: add(const unsigned nu, const Species &sp)
        {
            static const char * sep[2] = { " + ", "+" };

            // sanity
            if(nu<=0) throw Specific::Exception(CallSign,"0 for '%s'", sp.name.c_str());
            for(const Actor *a=list.head;a;a=a->next)
            {
                if( a->sp.name == sp.name )
                    throw Specific::Exception(CallSign,"multiple '%s'", sp.name.c_str());
            }

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

