
//! \file

#ifndef Y_Chemical_MixedEquilibrium_Included
#define Y_Chemical_MixedEquilibrium_Included 1


#include "y/chemical/reactive/equilibrium.hpp"
#include "y/protean/bare/heavy/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Protean::BareHeavyList<int> WList; //!< alias for list of weights
        typedef WList::NodeType             WNode; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Mixed Equilibrium
        //
        //
        //______________________________________________________________________
        class MixedEquilibrium : public Equilibrium
        {
        public:

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param eid mixed name
             \param top toplevel index
             \param tlk toplevel persistent constatns
             \param wl  list of weights
             \param el  list of corresponding equilibria
             */
            explicit MixedEquilibrium(const String &    eid,
                                      const size_t      top,
                                      const XReadable & tlk,
                                      WList &           wl,
                                      EList &           el);

            //! cleanup
            virtual ~MixedEquilibrium() noexcept;


        private:
            Y_Disable_Copy_And_Assign(MixedEquilibrium); //!< discarding
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
