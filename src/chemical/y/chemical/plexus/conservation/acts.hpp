
//! \file


#ifndef Y_Chemical_Conservation_Acts_Included
#define Y_Chemical_Conservation_Acts_Included 1


#include "y/chemical/plexus/conservation/act.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            //__________________________________________________________________
            //
            //
            //
            //! List of independent Acts of dependents Laws
            //
            //
            //__________________________________________________________________
            class Acts : public Object, public Ingress< const Act::List >
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! create from laws
                /**
                 \param xml      output
                 \param laws     pre-computed laws
                 \param primary  list of primary equilibria
                 \param topology primary topology matrix
                 */
                explicit Acts(XMLog         & xml,
                              const Laws    & laws);
                virtual ~Acts() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(Acts); //!< discarding
                Y_Ingress_Decl();                //!< helper
                Act::List alist; //!< acts

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                bool accepted(const Law &) noexcept; //!< \return true iff accepted by an existing act
                void tryMerge()            noexcept; //!< check recombination after acceptation
            };

        }

    }

}

#endif
