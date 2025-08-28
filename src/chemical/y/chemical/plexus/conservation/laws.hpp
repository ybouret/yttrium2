

//! \file


#ifndef Y_Chemical_Conservation_Laws_Included
#define Y_Chemical_Conservation_Laws_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/stream/xmlog.hpp"

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
            //! Conservation Laws
            //
            //
            //__________________________________________________________________
            class Laws : public Object, public Ingress< const Core::ListOf<Law> >, public Assembly
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Laws(XMLog &, const uMatrix &, const SList &); //!< setup
                virtual ~Laws() noexcept; //!< cleanup


            private:
                Y_Disable_Copy_And_Assign(Laws); //!< discarding
                Y_Ingress_Decl();                //!< helper
                CxxListOf<Law> list; //!< laws
            };

        }

    }

}

#endif

