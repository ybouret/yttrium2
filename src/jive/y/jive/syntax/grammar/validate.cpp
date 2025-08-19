#include "y/jive/syntax/grammar.hpp"
#include "y/container/ordered/data-book.hpp"
#include "y/jive/syntax/rule/wildcard/optional.hpp"
#include "y/jive/syntax/rule/wildcard/at-least.hpp"
#include "y/format/decimal.hpp"
#include "y/ascii/plural.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            typedef DataBook<> DBType;

            static void Visit(DBType &, const Rule * const);

            static inline
            void VisitWildcard(DBType &db, const Wildcard * const rule)
            {
                assert(rule);
                assert(db.search( static_cast<const Rule *>(rule)) );
                Visit(db, & rule->rule);
            }

            static inline
            void VisitLogical(DBType &db, const Logical * const rule)
            {
                assert(rule);
                assert(db.search( static_cast<const Rule *>(rule)) );

                for(const RuleNode *node = (*rule)->head;node;node=node->next)
                {
                    const Rule &r = **node;
                    Visit(db, &r);
                }
            }



            static inline
            void Visit(DBType &db, const Rule * const rule)
            {
                if( db.search( rule ) ) return;
                db |= rule;
                switch(rule->uuid)
                {
                    case Optional::UUID:
                    case AtLeast::UUID:
                        return VisitWildcard(db, dynamic_cast<const Wildcard *>(rule) );

                    case Aggregate::UUID:
                    case Alternate::UUID:
                        return VisitLogical(db, dynamic_cast<const Logical *>(rule) );
                }

            }


            void Grammar:: validate() const
            {
                if(rules.size<=0) throw Specific::Exception(lang->c_str(),"no rule");
                DBType::PoolType dp;
                DBType           db(dp);

                // visit top level rule
                Visit(db,rules.head);

                // check everyone was visited
                Manifest orphans;
                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    if(!db.search(rule)) orphans << *rule;
                }

                // validate
                const size_t lost = orphans->size;
                if(lost)
                {
                    String info;
                    const RuleNode *node = orphans->head;
                    info += *(**node).name;
                    for(node=node->next;node;node=node->next)
                    {
                        info += ',';
                        info += *(**node).name;
                    }
                    throw Specific::Exception(lang->c_str(),
                                              "%s orphan%s: %s",
                                              Decimal(lost).c_str(),
                                              ASCII::Plural::s(lost),
                                              info.c_str());
                }

            }
        }

    }

}
