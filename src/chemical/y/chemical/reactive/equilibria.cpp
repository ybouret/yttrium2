
#include "y/chemical/reactive/equilibria.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        const char * const Equilibria:: CallSign = "Equilibria";
        const char * const Equilibria:: CSID     = "set19";

        Equilibria:: ~Equilibria() noexcept
        {
        }

        Equilibria:: Equilibria() :
        db(),
        cs( GraphViz::ColorScheme::Query(CSID) )
        {

        }

        Equilibria::Iterator Equilibria:: begin() noexcept { return db.begin(); }
        Equilibria::Iterator Equilibria:: end()   noexcept { return db.end();   }



        size_t Equilibria:: nextTop() const noexcept
        {
            return db.size()+1;
        }

        void Equilibria:: record(Equilibrium * const eq)
        {
            assert(eq);
            const Equilibrium::Pointer p(eq);
            checkpoint(CallSign,"record");
            if(p->indx[TopLevel] != nextTop())
                throw Specific::Exception(CallSign,"invalid top index for '%s'", eq->name.c_str());
            if(!db.insert(p))
                throw Specific::Exception(CallSign,"multiple '%s'", eq->name.c_str());
            enroll(*eq);
        }


        Y_Ingress_Impl(Equilibria,db)

        std::ostream & operator<<(std::ostream &os, const Equilibria &eqs)
        {
            os << '{' << std::endl;
            for(Equilibria::ConstIterator it=eqs->begin();it != eqs->end(); ++it)
            {
                const Equilibrium &eq = **it;
                eqs.display(os << "    ",eq);
                const xreal_t K = Coerce(eq).K(0);
                const real_t  lK = K.log10();
                os << "'10^(" << lK << ")'";
                os << std::endl;
            }
            return os << '}';
        }

      

    }

}

