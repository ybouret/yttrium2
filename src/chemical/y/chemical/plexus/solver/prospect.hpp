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

            static SignType ByDecreasingAX(const Prospect &, const Prospect &) noexcept;

            const Status       st;
            const Equilibrium &eq;
            const xreal_t      eK;
            XWritable &        cc;
            xreal_t            xi;
            xreal_t            af;
            
        private:
            Y_Disable_Assign(Prospect);
        };

        typedef List<Prospect>  PList;
        typedef PList::NodeType PNode;
    }

}

#endif

