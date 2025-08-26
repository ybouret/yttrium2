//! \file

#ifndef Y_Chemical_Equilibrium_Included
#define Y_Chemical_Equilibrium_Included 1


#include "y/core/setup.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        class Equilibrium
        {
        public:
            static const char * const CallSign; //!< "Equilibrium"
            static const char * const Arrows;   //!< "<=>"
            static const char * const Prod;     //!< "Prod"
            static const char * const Reac;     //!< "Prod"


        private:
            Y_Disable_Copy_And_Assign(Equilibrium);
        };
    }

}

#endif

