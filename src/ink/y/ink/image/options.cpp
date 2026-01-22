
#include "y/ink/image/options.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Ink
    {

        const char * const Options:: CallSign = "Ink::Options";

        Options:: ~Options() noexcept
        {
        }

        Options:: Options() : OptionDB()
        {
        }

        Options:: Options(const Options &_) : OptionDB(_)
        {
        }


        String & Options:: operator[](const String &key)
        {
            {
                Option * const opt = search(key);
                if(opt) return **opt;
            }

            {
                Option opt = new String();
                if(!insert(key,opt)) throw Specific::Exception(CallSign,"couldn't insert '%s'", key.c_str());
                return *opt;
            }
        }

        String & Options:: operator[](const char * const key)
        {
            const String _(key);
            return (*this)[_];
        }

        const String & Options:: operator[](const String &key) const
        {
            const Option * const opt = search(key);
            if(!opt) throw Specific::Exception(CallSign,"no '%s'", key.c_str());
            return **opt;
        }

        const String & Options:: operator[](const char * const key) const
        {
            const String _(key);
            return (*this)[_];
        }

    }

}
