
#include "y/chemical/reactive/equilibria.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        const char * const Equilibria:: CallSign = "Equilibria";

        Equilibria:: ~Equilibria() noexcept
        {
        }

        Equilibria:: Equilibria() :
        db(),
        lvm( new Lua::State() )
        {

        }

        size_t Equilibria:: nextTop() const noexcept
        {
            return db.size()+1;
        }

        void Equilibria:: record(Equilibrium * const eq)
        {
            assert(eq);
            const Equilibrium::Pointer p(eq);
            if(p->indx[TopLevel] != nextTop())
                throw Specific::Exception(CallSign,"invalid top index for '%s'", eq->name.c_str());
            if(!db.insert(p))
                throw Specific::Exception(CallSign,"multiple '%s'", eq->name.c_str());
            enroll(*eq);
        }


        Y_Ingress_Impl(Equilibria,db)
    }

}

