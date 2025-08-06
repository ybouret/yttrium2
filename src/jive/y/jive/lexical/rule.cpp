
#include "y/jive/lexical/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {


            Rule:: Rule(const Tag   &   r,
                        const Motif &   m,
                        const Attribute a,
                        const bool      emit,
                        const Tag      &noData) noexcept :
            Object(),
            name(r),
            motif(m),
            attr(a),
            data(noData),
            deed(emit?Emit:Drop),
            next(0),
            prev(0)
            {
                assert(0 == data->length() );
            }

            Rule:: ~Rule() noexcept
            {
            }

            

        }

    }

}
