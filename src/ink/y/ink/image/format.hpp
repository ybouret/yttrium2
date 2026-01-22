
//! \file

#ifndef Y_Ink_Image_Format_Included
#define Y_Ink_Image_Format_Included 1

#include "y/ink/image/codec.hpp"
#include "y/jive/pattern/matching.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Format : public Codec
        {
        public:
            template <typename UID, typename EXT> inline
            explicit Format(const UID &uid, const EXT &ext) :
            Codec(uid),
            extension(ExtToPattern(ext))
            {

            }

            virtual ~Format() noexcept;

            Jive::Matching extension;

        private:
            Y_Disable_Copy_And_Assign(Format);
            template <typename EXT> static inline
            Jive::Pattern * ExtToPattern(const EXT &ext)
            {
                String rx = ext;
                return MakePattern(rx);
            }

            static Jive::Pattern * MakePattern(String &rx);

        };

    }

}

#endif // !Y_Ink_Image_Format_Included

