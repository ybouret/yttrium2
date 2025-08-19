#include "y/jive/syntax/grammar.hpp"
#include "y/system/exception.hpp"

#include "y/jive/syntax/rule/wildcard/optional.hpp"
#include "y/jive/syntax/rule/wildcard/at-least.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            
            Grammar:: ~Grammar() noexcept
            {
            }

           

            void  Grammar:: top(const Rule &rule) noexcept
            {
                assert(rules.owns(&rule));
                rules.moveToFront( & Coerce(rule) );
            }


            const Rule * Grammar:: queryRule(const String &rid) const noexcept
            {
                for(const Rule *r=rules.head;r;r=r->next)
                {
                    if( *(r->name) == rid ) return r;
                }
                return 0;
            }

            const Rule * Grammar:: queryRule(const Tag &rid) const noexcept
            {
                return queryRule(*rid);
            }

            const Rule * Grammar:: queryRule(const char * const rid) const
            {
                const String _(rid);
                return queryRule(_);
            }


            const Rule * Grammar:: queryRule(const char c) const
            {
                const String _(c);
                return queryRule(_);
            }

            void Grammar:: append(Rule *const rule)
            {
                assert(0!=rule);
                AutoPtr<Rule> guard( rule );
                if(queryRule(rule->name))
                    throw Specific::Exception(lang->c_str(),"mutliple rule '%s'", rule->name->c_str());
                Coerce(rules.pushTail(guard.yield())->pptr) = pptr;

            }

            Y_Ingress_Impl(Grammar,rules)


            String Grammar:: PreFormat(const Rule &rule)
            {
                if( rule.isTerminal() ) return *rule.name;
                return '(' + *rule.name + ')';
            }


            const Rule & Grammar:: opt(const Rule &rule)
            {
                assert( rules.owns( &rule ) );

                const String rid = PreFormat(rule) + '?';
                return add( new Optional(rid,rule) );
            }

            const Rule & Grammar:: oom(const Rule &rule)
            {
                const String rid = PreFormat(rule) + '+';
                return add( new AtLeast(rid,1,rule) );
            }

            const Rule & Grammar:: zom(const Rule &rule)
            {
                const String rid = PreFormat(rule) + '*';
                return add( new AtLeast(rid,0,rule) );
            }


            String Grammar:: buildName(const Manifest &manifest, const char sep) const
            {
                if(manifest->size<=0) throw Specific::Exception(lang->c_str(),"empty manifest to buildName");
                String res = '(';
                {
                    const RuleNode *node = manifest->head;
                    res += *(**node).name;
                    for(node=node->next;node;node=node->next)
                    {
                        res += sep; res += *(**node).name;
                    }
                }
                return res + ')';
            }

            const Rule & Grammar:: cat(const Rule &a, const Rule &b)
            {
                Manifest manifest; manifest << a << b;
                return create< AggregateIs<Grouping> >(manifest,AggSep);
            }


            const Rule & Grammar:: cat(const Rule &a, const Rule &b, const Rule &c)
            {
                Manifest manifest; manifest << a << b << c;
                return create< AggregateIs<Grouping> >(manifest,AggSep);
            }

            const Rule & Grammar:: pick(const Rule &a, const Rule &b)
            {
                Manifest manifest; manifest << a << b;
                return create<Alternate>(manifest,AltSep);
            }


            const Rule & Grammar:: pick(const Rule &a, const Rule &b, const Rule &c)
            {
                Manifest manifest; manifest << a << b << c;
                return create<Alternate>(manifest,AltSep);
            }


            

            OutputStream & Grammar:: viz(OutputStream &fp) const
            {
                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    rule->vizDecl(fp);
                }

                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    rule->vizPost(fp);
                }

                return fp;
            }

            void Grammar:: render() const
            {
                const String dotFile = *lang + ".dot";
                Render(dotFile,*this);
            }

            
        }

    }

}
