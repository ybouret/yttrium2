
//! \file

#ifndef Y_Jive_TagDB_Included
#define Y_Jive_TagDB_Included 1

#include "y/jive/tag.hpp"
#include "y/container/associative/suffix/set.hpp"

namespace Yttrium
{
    namespace Jive
    {

        typedef SuffixSet<String,Tag> TagSet; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Database of Tag for components setup
        //
        //
        //______________________________________________________________________
        class TagDB : public TagSet
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit TagDB();
            virtual ~TagDB() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param id textual key \return new/found tag
            template <typename ID> inline
            Tag operator[](const ID &id)
            {
                return get(id);
            }

            //! \return tag from input, with optional name
            Tag read(InputStream &, const char * const = 0);

        private:
            Y_Disable_Copy_And_Assign(TagDB); //!< discarding
            Tag get(const String &);          //!< \return tag
            Tag get(const char * const);      //!< \return tag
            Tag get(const char);              //!< \return tag
        };

    }

}

#endif

