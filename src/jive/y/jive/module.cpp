
#include "y/jive/module.hpp"
#include "y/stream/libc/input.hpp"
#include "y/stream/memory/input.hpp"

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

        InputStream * Module:: OpenData_(const void * const entry, const size_t count)
        {
            assert( Good(entry,count) );
            return new MemoryInput(entry,count);
        }

        Char * Module:: query()
        {
            static Char::Cache &pool = Char::CacheInstance();
            char   c = 0;
            if(!input->query(c)) return 0;
            dot();
            const Context &ctx = *this;
			const uint8_t b = (uint8_t)c;
            return pool.summon(b,ctx);
        }

        Module:: Module(const Tag &tag, const Input &inp) noexcept:
        Context(tag),
        input(inp)
        {
        }

    }

}
