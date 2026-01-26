

//! \file

#ifndef Y_Ink_Format_TIFF_Included
#define Y_Ink_Format_TIFF_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {
        
        //______________________________________________________________________
        //
        //
        //
        //! TIFF
        //
        //
        //______________________________________________________________________
        class FormatTIFF : public Format
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "TIFF"
            static const char * const Extension; //!< "tif|tiff"
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormatTIFF();           //!< setup
            virtual ~FormatTIFF() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            virtual void  save(const Image   &       image,
                               const String  &       fileName,
                               const Options * const options) const;

            virtual Image load(const String  &       fileName,
                               const Options * const options) const;

            //! TIFF count_directories
            /**
             \param fileName file name
             \return number of directories
             */
            static size_t CountDirectories(const String &fileName);

        private:
            Y_Disable_Copy_And_Assign(FormatTIFF); //!< discarding
        };
    }

}

#endif // !Y_Ink_Format_TIFF_Included

