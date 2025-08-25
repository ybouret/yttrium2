//! \file


#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1


#include "y/jive/syntax/node.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef Jive::XNode XNode;
        typedef Jive::XCode XCode;

        //______________________________________________________________________
        //
        //
        //
        //! Species Formula, keep parsed Xnode
        //
        //
        //______________________________________________________________________
        class Formula
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Formula"
            static const char * const Name;     //!< "Name"
            static const char * const Body;     //!< "Body"
            static const char * const Mult;     //!< "Mult"
            static const char * const Z;        //!< "Z"


            virtual ~Formula() noexcept;

        private:
            Y_Disable_Assign(Formula);
        };

    }

}

#endif

