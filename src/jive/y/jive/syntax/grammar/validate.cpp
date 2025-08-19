#include "y/jive/syntax/grammar.hpp"
#include "y/container/ordered/data-book.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            void Grammar:: validate() const
            {
                if(rules.size<=0) throw Specific::Exception(lang->c_str(),"no rule");
                DataBook<>::PoolType dp;
                DataBook<>           db(dp);

                db += rules.head;

            }
        }

    }

}
