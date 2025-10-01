#include "y/chemical/formula.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Formula:: CallSign = "Formula";
        const char * const Formula:: Name     = "Name";
        const char * const Formula:: Body     = "Body";
        const char * const Formula:: Mult     = "Mult";
        const char * const Formula:: Z        = "Z";


        Formula:: ~Formula() noexcept
        {

        }

        Formula:: Formula(XNode * const node)  noexcept :
        code(node)
        {
            assert(code->defines<Formula>());
        }

        Formula:: Formula(const XCode &args)  noexcept :
        code(args)
        {
            assert( code->defines<Formula>() );
        }

        Formula:: Formula(const Formula &f) noexcept :
        code(f.code)
        {

        }

        String Formula:: ToText(const String &data)
        {
            const Formula f(data);
            int z = 0;
            return f.text(&z);
        }

        String Formula:: ToHTML(const String &data)
        {
            const Formula f(data);
            return f.html();
        }

        String Formula:: ToLaTeX(const String &data)
        {
            const Formula f(data);
            return f.laTeX();
        }


    }

}

