
//! \file

#ifndef Y_Ink_Format_TIFFxx_Included
#define Y_Ink_Format_TIFFxx_Included 1

#include "y/ink/image.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Ink
    {
        
        //__________________________________________________________________
        //
        //
        //! wrapper for a TIFF
        //
        //__________________________________________________________________
        class tiffxx
        {
        public:
            virtual ~tiffxx() noexcept; //!< cleanup

        protected:
            //! TIFFopen
            /**
             \param fileName file anme
             \param mode  TIFF mode
             */
            explicit tiffxx(const String &fileName, const char * const mode);
            void * const handle; //!< TIFF

        private:
            Y_Disable_Copy_And_Assign(tiffxx); //!< dicarding
        };

        //__________________________________________________________________
        //
        //
        //! input TIFF
        //
        //__________________________________________________________________
        class itiff: public tiffxx
        {
        public:
            explicit itiff(const String &fileName); //!< setup \param fileName file name
            virtual ~itiff() noexcept;              //!< cleanup

            size_t width();                       //!< \return image width
            size_t height();                      //!< \return image height
            size_t count_directories();           //!< \return count directories
            bool   load(Pixmap<RGBA> &img);       //!< \param img image to loade img.w = width, img.h = height \return success
            void   set_directory(const size_t n); //!< set directory \param n image index


            static size_t width_of(const String &);        //!< \return helper to get width
            static size_t height_of(const String &);       //!< \return helper to get height
            static size_t directories_of(const String &);  //!< \return helper to get directories

            static size_t width_of(const char * const );        //!< \return wrapper
            static size_t height_of(const char * const );       //!< \return wrapper
            static size_t directories_of(const char * const);   //!< \return wrapper

        private:
            Y_Disable_Copy_And_Assign(itiff); //!< discarding
        };

        //__________________________________________________________________
        //
        //
        //! output TIFF
        //
        //__________________________________________________________________
        class otiff: public tiffxx
        {
        public:
            explicit otiff(const String &); //!< setup
            virtual ~otiff() noexcept;      //!< cleanup


        private:
            Y_Disable_Copy_And_Assign(otiff); //!< discarding
        };

        
    }
}

#endif // !Y_Ink_Format_TIFFxx_Included
