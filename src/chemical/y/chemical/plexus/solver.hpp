
//! \file


#ifndef Y_Chemical_Solver_Included
#define Y_Chemical_Solver_Included 1


#include "y/chemical/plexus/cluster.hpp"
#include "y/protean/solo/heavy/list.hpp"
#include "y/chemical/plexus/solve1d.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Prospect
        {
        public:

            Prospect();
            Prospect(const Prospect &);
            ~Prospect() noexcept;

        private:
            Y_Disable_Assign(Prospect);
        };

        typedef List<Prospect>  PList;
        typedef PList::NodeType PNode;


        class Solver
        {
        public:
            explicit Solver(const Cluster &);
            virtual ~Solver() noexcept;

            void buildProspects(XWritable &C, const Level L, const XReadable &K);

        private:
            const Cluster &cluster;
            XArray         Csub;
            XMatrix        Ceq;
            PList          propects;
            Solve1D        solve1d;

        };
    }

}

#endif
