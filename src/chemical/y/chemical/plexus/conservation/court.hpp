

//! \file


#ifndef Y_Chemical_Conservation_Court_Included
#define Y_Chemical_Conservation_Court_Included 1


#include "y/chemical/plexus/conservation/judge.hpp"
#include "y/chemical/plexus/clusters.hpp"


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
            //! Court of Judges per Act
            //
            //
            //__________________________________________________________________
            class Court : public Object, public Ingress< const Core::ListOf<Judge> >
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Court(const Clusters &); //!< setup
                virtual ~Court() noexcept;        //!< cleanup

                //! trial thru each Judge
                /**
                 \param xml  output
                 \param Ctop TopLevel concentrations
                 \param Itop TopLevel accumulator
                 */
                void trial(XMLog &xml, XWritable &Ctop, Accumulator &Itop);

            private:
                Y_Disable_Copy_And_Assign(Court); //!< discarding
                Y_Ingress_Decl();                 //!< helper
                CxxListOf<Judge> jlist;           //!< judges

            };

        }

    }

}

#endif

