
//! \file

#ifndef Y_Chemical_MixedEquilibrium_Included
#define Y_Chemical_MixedEquilibrium_Included 1


#include "y/chemical/reactive/equilibrium.hpp"
#include "y/protean/bare/heavy/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Protean::BareHeavyList<int> WList;
        typedef WList::NodeType             WNode;

        class MixedEquilibrium : public Equilibrium
        {
        public:
            
            explicit MixedEquilibrium(const String &    eid,
                                      const size_t      top,
                                      const XReadable & tlk,
                                      WList &           wl,
                                      EList &           el);

            virtual ~MixedEquilibrium() noexcept;


        private:
            Y_Disable_Copy_And_Assign(MixedEquilibrium);
            virtual xreal_t getK(const xreal_t);
            const XReadable &topK;  //!< top-level constatns
            const WList      wlist; //!< list of weights
            const EList      elist; //!< list of equilibria
            XMul             numer; //!< numerator
            XMul             denom; //!< denominator

        };

    }

}

#endif
