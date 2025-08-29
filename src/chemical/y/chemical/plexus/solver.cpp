
#include "y/chemical/plexus/solver.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        Solver:: ~Solver() noexcept
        {

        }

        Solver:: Solver(const Cluster &cl) :
        cluster(cl),
        Csub(cluster.slist->size),
        Ceq(cluster->size(),cluster.slist->size)
        {
            
        }


        void Solver:: buildProspects(XWritable &C, const Level L, const XReadable &K)
        {
            // create starting point
            cluster.copy(Csub,SubLevel,C,L); // import phase space
            propects.free();

            bool emergency = false;
            for(const ENode *en = (**cluster).head; en; en=en->next )
            {
                const Equilibrium &eq = **en;
                const Status       st = eq.status(Csub, SubLevel);
                XWritable         &cc = Ceq[propects->size+1];
                switch( st )
                {
                    case Blocked:  continue;
                    case Critical:
                        emergency = true;
                        break;

                    case Running:
                        if(emergency) continue;
                        break;
                }

                assert(Running == st || Critical == st);
                const xreal_t xi = solve1d( eq, eq(K,TopLevel), cc, SubLevel, Csub);
                

            }

        }

    }

}
