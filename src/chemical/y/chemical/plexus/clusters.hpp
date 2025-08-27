//! \file


#ifndef Y_Chemical_Clusters_Included
#define Y_Chemical_Clusters_Included 1


#include "y/chemical/plexus/cluster.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Clusters : public Ingress< Core::ListOf<Cluster> >
        {
        public:

            static const char * const CallSign;

            explicit Clusters(XMLog &xml, Equilibria &eqs);
            virtual ~Clusters() noexcept;


        private:
            Y_Disable_Copy_And_Assign(Clusters);
            Y_Ingress_Decl();

            CxxListOf<Cluster> list;
        };
    }

}

#endif

