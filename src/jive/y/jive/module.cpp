
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
            const Context &ctx = *this;
            return pool.summon(c,ctx);
        }

        Module:: Module(const Tag &tag, const Input &inp) noexcept:
        Context(tag),
        input(inp)
        {
        }

    }

}
