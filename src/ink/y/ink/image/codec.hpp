

//! \file

#ifndef Y_Ink_Image_Codec_Included
#define Y_Ink_Image_Codec_Included 1

#include "y/ink/image.hpp"
#include "y/object/counted.hpp"
#include "y/ink/image/options.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Codec : public CountedObject
        {
        protected:
            template <typename UID> inline
            explicit Codec(const UID &uid) : CountedObject(), name(uid) {}

        public:
            virtual ~Codec() noexcept;

            virtual void save(const Image &, const String &) = 0;

            const String & key() const noexcept;


            const String name;
            
        private:
            Y_Disable_Copy_And_Assign(Codec);
        };
    }

}

#endif // !Y_Ink_Image_Codec_Included

