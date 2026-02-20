
//! \file

#ifndef Y_Ink_Image_FormatBMP_Included
#define Y_Ink_Image_FormatBMP_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! default BITMAP format
        //
        //
        //______________________________________________________________________
        class FormatBMP : public Format
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;  //!< "BMP"
            static const char * const Extension; //!< "bmp"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormatBMP();          //!< setup
            virtual ~FormatBMP() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Inteface
            //
            //__________________________________________________________________
            virtual void  onSave(const Image &, const String &, const Options * const) const;
            virtual Image onLoad(const String &, const Options * const)                const;


        private:
            Y_Disable_Copy_And_Assign(FormatBMP); //!< discarding
        };

    }

}

#endif // !Y_Ink_Image_FormatBMP_Included

