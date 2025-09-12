//! \file


#ifndef Y_Chemical_Conservation_Act_Included
#define Y_Chemical_Conservation_Act_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/reactive/equilibrium.hpp"

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
            //! Act of shared species Laws
            //
            //
            //__________________________________________________________________
            class Act : public Object, public Ingress< const LList >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Act> List; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Act(const Law &); //!< setup with first law
                virtual ~Act() noexcept;   //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                bool accepts(const Law &) const noexcept; //!< \return true iff common species
                bool accepts(const Act &) const noexcept; //!< \return true iff common species
                void connect(const Law &);                //!< connect law to this act
                void combine(Act &);                      //!< combine foreign act to this acet

                //! query involved equilibria
                /**
                 \param primary  list of primary equilibria
                 \param topology primary topology matrix
                 */
                void query(const EList   & primary,
                           const iMatrix & topology);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(Act); //!< discarding
                Y_Ingress_Decl();               //!< helper
                LList       list; //!< laws

            public:
                const SList slist; //!< species
                const EList elist; //!< primary involved equilibria
                Act *       next;  //!< for list
                Act *       prev;  //!< for list
            };
        }

    }

}

#endif


