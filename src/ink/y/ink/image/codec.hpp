//! \file

#ifndef Y_Ink_Image_Codec_Included
#define Y_Ink_Image_Codec_Included 1

#include "y/ink/image.hpp"
#include "y/object/counted.hpp"
#include "y/ink/image/options.hpp"
#include "y/ink/ops.hpp"
#include "y/ink/ops/minmax.hpp"
#include "y/color/ramp.hpp"

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
            virtual void  onSave(const Image  &, const String &, const Options * const) const = 0;

            //! \return image from file with optional options
            virtual Image onLoad(const String &, const Options * const)                 const = 0;



            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept; //!< \return name

            void  save(const Image &, const String &,     const Options * const) const; //!< save alias
            void  save(const Image &, const char * const, const Options * const) const; //!< save alias
            Image load( const String &,     const Options * const)               const; //!< \return load alias
            Image load( const char * const, const Options * const)               const; //!< \return load alias

            //! save with conversion
            /**
             \param broker   cpu broker
             \param toRGBA   return RGBA from T
             \param pixmap   source pixmap
             \param fileName output file name
             \param options  output options
             */
            template <typename T, typename TO_RGBA> inline
            void save(Broker              & broker,
                      TO_RGBA             & toRGBA,
                      const Pixmap<T>     & pixmap,
                      const String        & fileName,
                      const Options * const options) const
            {
                Image image(pixmap.w,pixmap.h);
                Ops::Convert(broker,image,toRGBA,pixmap);
                save(image,fileName,options);
            }

            //! save with conversion, alias
            /**
             \param broker   cpu broker
             \param toRGBA   return RGBA from T
             \param pixmap   source pixmap
             \param fileName output file name
             \param options  output options
             */
            template <typename T, typename TO_RGBA> inline
            void save(Broker              & broker,
                      TO_RGBA             & toRGBA,
                      const Pixmap<T>     & pixmap,
                      const char * const    fileName,
                      const Options * const options) const
            {
                const String _(fileName);
                save(broker,toRGBA,pixmap,_,options);
            }

            //! save with a color ramp and automatic scaling
            /**
             \param colorRamp precomputed color ramp
             \param broker    cpu broker
             \param pixmap    source pixmap
             \param fileName  output file name
             \param options   output options
             */
            template <typename T,typename FILENAME> inline
            void save(const Color::Ramp &   colorRamp,
                      Broker            &   broker,
                      const Pixmap<T>   &   pixmap,
                      const FILENAME    &   fileName,
                      const Options * const options) const
            {
                const PixelRange<T>    px = MinMax::Of(broker,pixmap);
                const Color::RampOf<T> ramp(colorRamp,px.vmin,px.vmax);
                std::cerr << "px.min=" << px.vmin << ", px.max=" << px.vmax << " / #colors=" << ramp.count << std::endl;
                save(broker,ramp,pixmap,fileName,options);
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

