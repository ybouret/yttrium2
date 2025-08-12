#include "y/jive/syntax/grammar.hpp"
#include "y/exception.hpp"
namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            
            Grammar:: ~Grammar() noexcept
            {
            }

            const Rule * Grammar:: query(const String &rid) const noexcept
            {
                for(const Rule *r=rules.head;r;r=r->next)
                {
                    if( *(r->name) == rid ) return r;
                }
                return 0;
            }

            const Rule * Grammar:: query(const Tag &rid) const noexcept
            {
                return query(*rid);
            }

            const Rule * Grammar:: query(const char * const rid) const
            {
                const String _(rid);
                return query(_);
            }


            void Grammar:: append(Rule *const rule)
            {
                assert(0!=rule);
                AutoPtr<Rule> guard( rule );
                if(query(rule->name)) throw Specific::Exception(name->c_str(),"mutliple rule '%s'", rule->name->c_str());
                Coerce(rules.pushTail(rule)->gptr) = this;

            }

            Y_Ingress_Impl(Grammar,rules)
        }

    }

}
