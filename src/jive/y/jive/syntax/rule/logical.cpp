
#include "y/jive/syntax/rule/logical.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {


            Logical:: ~Logical() noexcept
            {
            }

            
            OutputStream & Logical:: vizPost(OutputStream &fp) const
            {
                unsigned indx = 0;
                for(const RuleNode *node= (*this)->head;node;node=node->next)
                {
                    const Rule &sub = **node;
                    to(&sub,fp);
                    Endl( fp("[label=\"%u\"]",++indx) );
                }
                return fp;
            }





        }

    }

}

#include "y/system/exception.hpp"
#include "y/jive/parser.hpp"
namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Logical & Logical:: operator<<(const char C)
            {
                if(!pptr) throw Specific::Exception(name->c_str(),"no linked Parser!");
                { Manifest &self = *this; self << (*pptr)[C]; }
                return *this;
            }

            Logical & Logical:: operator<<(const Rule &rule)
            {
                { Manifest &self = *this; self << rule; }
                return *this;
            }


        }
    }

}
