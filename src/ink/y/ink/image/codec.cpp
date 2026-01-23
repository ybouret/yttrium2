
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


    }

}
