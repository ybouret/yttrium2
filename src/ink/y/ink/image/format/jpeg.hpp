//! \file

#ifndef Y_Ink_Format_JPEG_Included
#define Y_Ink_Format_JPEG_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {


        //______________________________________________________________________
        //
        //
        //
        //! JPEG Bitmap
        //
        //
        //______________________________________________________________________
        class FormatJPEG : public Format
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;  //!< "JPEG"
            static const char * const Extension; //!< "jpe?g"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormatJPEG();           //!< setup
            virtual ~FormatJPEG() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! saving
            /**
             \param options quality=[10..100], default to 75
             */
            virtual void  save(const Image  &,
                               const String &,
                               const Options * const options) const;

            virtual Image load(const String & ,
                               const Options * const) const;

        private:
            Y_Disable_Copy_And_Assign(FormatJPEG); //!< discarding
        };
    }

}

#endif // !Y_Ink_Format_JPEG_Included

