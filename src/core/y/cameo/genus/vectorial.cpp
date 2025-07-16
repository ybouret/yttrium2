
#include "y/cameo/genus/vectorial.hpp"
#include "y/core/text.hpp"
#include <cstring>
#include <cassert>

namespace Yttrium
{
    namespace Cameo
    {
        VectorialGenus:: VectorialGenus(const char * const sid) noexcept :
        identifier()
        {
            static const char prolog[] = "Vectorial";
            assert(0!=sid);

            char * const target = (char *)identifier;
            memset(target,0,sizeof(identifier));
            Core::Text::Copy(target,sizeof(identifier),prolog);
            Core::Text::Add(target,sizeof(identifier),sid);
        }


        VectorialGenus:: ~VectorialGenus() noexcept
        {
            
        }
    }

}

