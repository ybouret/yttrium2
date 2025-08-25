//! \file


#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1


#include "y/jive/syntax/node.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef Jive::XNode                XNode;
        typedef Jive::XCode                XCode;
        typedef Jive::Syntax::InternalNode XTree;

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

            Formula(XNode * const)  noexcept;
            Formula(const XCode &)  noexcept;
            Formula(const Formula&) noexcept;
            virtual ~Formula() noexcept;

            String text(int * const z) const;

            const XCode code;
        private:
            Y_Disable_Assign(Formula);
        };

    }

}

#endif

