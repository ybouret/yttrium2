
#include "y/jive/module.hpp"
#include "y/stream/libc/input.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Module:: ~Module() noexcept
        {
        }


        InputStream  * Module:: OpenFile_(const String &fileName)
        {
            return new InputFile(fileName);
        }

        Char * Module:: query()
        {
            static Char::Cache &pool = Char::CacheInstance();
            char   c = 0;
            if(!input->query(c)) return 0;
            dot();
            return pool.summon(c,*this);
        }

    }

}
