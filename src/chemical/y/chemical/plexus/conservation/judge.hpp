

//! \file


#ifndef Y_Chemical_Conservation_Judge_Included
#define Y_Chemical_Conservation_Judge_Included 1


#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Judge : public Object
            {
            public:
                explicit Judge(const Laws &);
                virtual ~Judge() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Judge);
            };
        }

    }

}

#endif

