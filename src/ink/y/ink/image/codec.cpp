
#include "y/ink/image/codec.hpp"


namespace Yttrium
{
    namespace Ink
    {

        Codec:: ~Codec() noexcept
        {
        }

        const String & Codec:: key() const noexcept { return name; }


        const String * Options:: Query(const Options * const options, const String &key) noexcept
        {
            if(!options) return 0;
            const Option * const opt = options->search(key);
            if(!opt) return 0;
            return & **opt;
        }


        const String * Options:: Query(const Options * const options, const char * const key)
        {
            const String _(key);
            return Query(options,_);
        }

        void Codec:: save(const Image &image, const String &fileName, const Options *const options) const
        {
            onSave(image,fileName,options);
        }


        void Codec:: save(const Image &image, const char * const fileName, const Options *const options) const
        {
            const String _(fileName);
            save(image,_,options);
        }

        Image Codec:: load(const String &fileName, const Options * const options) const
        {
            return onLoad(fileName,options);
        }

        Image Codec:: load(const char * const fileName, const Options * const options) const
        {
            const String _(fileName);
            return load(_,options);
        }


    }

}
