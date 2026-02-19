//! \file

#ifndef Y_Ink_Image_Codec_Included
#define Y_Ink_Image_Codec_Included 1

#include "y/ink/image.hpp"
#include "y/object/counted.hpp"
#include "y/ink/image/options.hpp"
#include "y/ink/ops.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! I/O interface for Image
        //
        //
        //______________________________________________________________________
        class Codec : public CountedObject
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup \param uid name
            template <typename UID> inline
            explicit Codec(const UID &uid) : CountedObject(), name(uid) {}

        public:
            virtual ~Codec() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! save image into file with optional options
            virtual void  save(const Image  &, const String &, const Options * const) const = 0;

            //! \return image from file with optional options
            virtual Image load(const String &, const Options * const)                 const = 0;
            

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept; //!< \return name

            template <typename T, typename TO_RGBA> inline
            void saveAs(Broker              & broker,
                        TO_RGBA             & toRGBA,
                        const Pixmap<T>     & pixmap,
                        const String        & fileName,
                        const Options * const options) const
            {
                Image image(pixmap.w,pixmap.h);
                Ops::Convert(broker,image,toRGBA,pixmap);
                save(image,fileName,options);
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String name; //!< identifier

        private:
            Y_Disable_Copy_And_Assign(Codec); //!< discarding
        };

    }

}

#endif // !Y_Ink_Image_Codec_Included

