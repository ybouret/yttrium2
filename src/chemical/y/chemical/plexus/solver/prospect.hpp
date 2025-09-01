//! \file


#ifndef Y_Chemical_Prospect_Included
#define Y_Chemical_Prospect_Included 1

#include "y/chemical/reactive/equilibrium.hpp"
#include "y/protean/solo/heavy/list.hpp"
#include "y/chemical/type/assembly.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        class Prospect
        {
        public:
            Prospect(const Status        _st,
                     const Equilibrium & _eq,
                     const xreal_t       _eK,
                     XWritable &         _cc,
                     xreal_t             _xi) noexcept;

            Prospect(const Prospect &) noexcept;
            ~Prospect() noexcept;

            std::ostream & display(std::ostream &, const Assembly &) const;

            static SignType ByDecreasingXi(const Prospect &, const Prospect &) noexcept;
            static SignType ByIncreasingWo(const Prospect &, const Prospect &) noexcept;

            const Status       st;   //!< status
            const Equilibrium &eq;   //!< equilibrium
            const xreal_t      eK;   //!< current e.K
            XWritable &        cc;   //!< optimized phases space
            xreal_t            xi;   //!< optimized extent
            xreal_t            Wo;   //!< optimized rms
            xreal_t            W1;   //!< rms at solve1d
            
        private:
            Y_Disable_Assign(Prospect);
        };

        typedef List<Prospect>  PList;
        typedef PList::NodeType PNode;
    }

}

#endif

