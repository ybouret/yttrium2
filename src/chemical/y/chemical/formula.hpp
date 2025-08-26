//! \file


#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1


#include "y/chemical/weasel/types.hpp"


namespace Yttrium
{
    namespace Chemical
    {
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

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Formula(XNode * const)  noexcept; //!< setup
            Formula(const XCode &)  noexcept; //!< setup
            Formula(const Formula&) noexcept; //!< duplicate
            virtual ~Formula()      noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String text(int * const z) const; //!< \param z optional charge address \return converted to text
            String html()              const; //!< \return converted to html

            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const XCode code; //!< shared binary representation
        private:
            Y_Disable_Assign(Formula); //!< discarding
        };

    }

}

#endif

