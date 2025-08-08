
//! \file

#ifndef Y_Jive_TagDB_Included
#define Y_Jive_TagDB_Included 1

#include "y/jive/tag.hpp"
#include "y/container/associative/suffix/set.hpp"

namespace Yttrium
{
    namespace Jive
    {

        typedef SuffixSet<String,Tag> TagSet;

        class TagDB : public TagSet
        {
        public:
            explicit TagDB();
            virtual ~TagDB() noexcept;

            template <typename ID> inline
            Tag operator[](const ID &id)
            {
                return get(id);
            }

            Tag read(InputStream &, const char * const = 0);

        private:
            Y_Disable_Copy_And_Assign(TagDB);
            Tag get(const String &);
            Tag get(const char * const);
            Tag get(const char);
        };

    }

}

#endif

