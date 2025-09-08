
//! \file


#ifndef Y_Chemical_SteadyState_Included
#define Y_Chemical_SteadyState_Included 1


#include "y/chemical/plexus/solver.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class SteadyState : public Object, public Ingress< Core::ListOf<Solver> >
        {
        public:
            explicit SteadyState(const Clusters &);
            virtual ~SteadyState() noexcept;

            void solve(XMLog &xml, XWritable & Ctop, const XReadable & Ktop);

        private:
            Y_Disable_Copy_And_Assign(SteadyState);
            Y_Ingress_Decl();
            CxxListOf<Solver> sl;
        };
    }
}

#endif

