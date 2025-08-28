
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

            explicit MixedEquilibrium(const String &eid,
                                      const size_t  top,
                                      const XReadable & tlk,
                                      WList &           wl,
                                      EList &           el);

            virtual ~MixedEquilibrium() noexcept;


        private:
            Y_Disable_Copy_And_Assign(MixedEquilibrium);
            virtual xreal_t getK(const xreal_t);
            const XReadable &topK;
            const WList      wlist;
            const EList      elist;
            XMul             xmul;
        };

    }

}

#endif
