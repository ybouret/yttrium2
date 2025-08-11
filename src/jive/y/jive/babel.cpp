
#include "y/jive/babel.hpp"

namespace Yttrium
{
    namespace Jive
    {
        const char * const Babel::CallSign = "Jive::Babel";
        
        Babel:: ~Babel() noexcept
        {
        }

        Babel:: Babel() :
        lexicalDB()
        {

            lexicalInit();
        }

        void Babel:: display(std::ostream &os,size_t indent) const
        {
            init(os,indent);

            quit(os,indent);
        }

    }
}
