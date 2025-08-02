//! \file

#ifndef Y_Jive_Source_Included
#define Y_Jive_Source_Included 1

#include "y/jive/token.hpp"
#include "y/jive/module.hpp"

namespace Yttrium
{
    namespace Jive
    {


        class Source
        {
        public:
            explicit Source(Module * const) noexcept;
            virtual ~Source() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Source);
            ArcPtr<Module> handle;
            Token          buffer;

        };
    }

}

#endif

