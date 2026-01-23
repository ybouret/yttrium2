
//! \file

#ifndef Y_Ink_Image_FormatBMP_Included
#define Y_Ink_Image_FormatBMP_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class FormatBMP : public Format
        {
        public:
            static const char * const CallSign;  //!< "BMP"
            static const char * const Extension; //!< "bmp"

            explicit FormatBMP();
            virtual ~FormatBMP() noexcept;


            virtual void  save(const Image &, const String &, const Options * const) const;
            virtual Image load(const String &, const Options * const)                const;


        private:
            Y_Disable_Copy_And_Assign(FormatBMP);
        };

    }

}

#endif // !Y_Ink_Image_FormatBMP_Included

