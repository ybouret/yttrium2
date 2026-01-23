//! \file

#ifndef Y_Ink_Format_PNG_Included
#define Y_Ink_Format_PNG_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! Raw RGB Bitmap
        //
        //
        //______________________________________________________________________
        class FormatPNG : public Format
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;  //!< "PNG"
            static const char * const Extension; //!< "png"
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormatPNG();           //!< setup
            virtual ~FormatPNG() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! saving
            /**
             \param options alpha=[true|false], level=[0..9]
             */
            virtual void  save(const Image   &,
                               const String  &,
                               const Options * const options) const;

            virtual Image load(const String  &,
                               const Options *) const;

        private:
            Y_Disable_Copy_And_Assign(FormatPNG); //!< discarding
        };
    }

}

#endif // !Y_Ink_Format_PNG_Included

