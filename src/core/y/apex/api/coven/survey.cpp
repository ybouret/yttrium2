#include "y/apex/api/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {
        Survey:: Survey(QVector::Pool &vp) noexcept :
        list(),
        pool(vp),
        calls(0)
        {
        }

        Survey:: ~Survey() noexcept
        {
            reset();
        }
        
        void Survey:: reset() noexcept
        {
            Coerce(calls) = 0;
            while(list.size) pool.store( list.popTail() );
        }


        Survey::ConstInterface & Survey:: locus() const noexcept
        {
            return list;
        }
    }

}


