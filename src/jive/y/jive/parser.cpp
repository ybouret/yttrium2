
#include "y/jive/parser.hpp"


namespace Yttrium
{
    namespace Jive
    {

        Parser:: ~Parser() noexcept {}


        const Syntax::Rule & Parser:: link(const Lexical::Rule &lr, const Syntax::Activity activity)
        {
            try { return terminal(lr.name,activity,lr.motif->univocal()); }
            catch(...) { emergencyTrim(); throw; }
        }
    }

}
