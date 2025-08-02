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
            virtual ~Tag()      noexcept; //!< cleanup

            //! setup \param name any compatible name
            template <typename T>
            inline Tag(const CopyOf_ &, const T &name) :
            TagType( new String(name) )
            {
            }


        private:
            Y_Disable_Assign(Tag); //!< discard
        };

    }
}

#endif

