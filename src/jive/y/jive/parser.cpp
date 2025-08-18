
#include "y/jive/parser.hpp"
#include "y/ascii/printable.hpp"
#include "y/system/exception.hpp"

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

        const Syntax::Rule & Parser:: link(const Tag &tag)
        {
            return terminal(tag,Syntax::Regular,false);
        }


        const Syntax::Rule & Parser:: operator[](const char c)
        {
            if(const Rule *rule=queryRule(c))
            {
                if(!rule->isTerminal()) throw Specific::Exception(lang->c_str(),"rule '%s' is not a Terminal",ASCII::Printable::Text(c));
                return *rule;
            }
            return mark(c);
        }

    }

}
