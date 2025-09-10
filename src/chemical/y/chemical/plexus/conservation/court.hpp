
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
            //! Assembly of Judges
            //
            //
            //__________________________________________________________________
            class Court : public Ingress< const Core::ListOf<Judge> >
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

            private:
                Y_Disable_Copy_And_Assign(Court); //!< discarding
                Y_Ingress_Decl();                 //!< helper
                CxxListOf<Judge> judges;          //!< judges for optional laws per cluster
            };
        }

    }

}

#endif
