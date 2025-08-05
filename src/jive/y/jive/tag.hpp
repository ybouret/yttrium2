//! \file

#ifndef Y_Jive_Tag_Included
#define Y_Jive_Tag_Included 1

#include "y/string.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //! base string pointer for tag
        typedef Keyed<String, ArcPtr<const String> > TagType;

        //______________________________________________________________________
        //
        //
        //
        //! Tag for multiple string references
        //
        //
        //______________________________________________________________________
        class Tag : public TagType
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Tag(String * const) noexcept; //!< direct setup
            Tag(const Tag &)    noexcept; //!< duplicate
            Tag(const String &);          //!< setup
            Tag(const char * const);      //!< setup
            Tag(const char);              //!< setup
            virtual ~Tag()      noexcept; //!< cleanup



        private:
            Y_Disable_Assign(Tag); //!< discard
        };

    }
}

#endif

