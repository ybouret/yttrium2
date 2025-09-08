
#include "y/chemical/plexus/steady-state.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        SteadyState:: SteadyState(const Clusters &cls) :
        solvers(),
        clusters(cls)
        {
            for(const Cluster *cl=cls->head;cl;cl=cl->next)
                solvers.pushTail( new Solver(*cl) );
        }

        SteadyState:: ~SteadyState() noexcept
        {
            
        }

        void SteadyState:: solve(XMLog &xml, XWritable & Ctop)
        {
            Y_XML_Section(xml,"SteadyState");
            for(Solver *solver=solvers.head;solver;solver=solver->next)
            {
                solver->forward(xml,Ctop,clusters.K);
            }
        }


        Y_Ingress_Impl(SteadyState,solvers)

    }
}
