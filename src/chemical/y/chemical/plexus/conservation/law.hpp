
//! \file


#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1


#include "y/chemical/reactive/actors.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            class Law : public Actors
            {
            public:
                explicit Law();
                virtual ~Law() noexcept;
                Y_OSTREAM_PROTO(Law);
                
                Law * next;
                Law * prev;
            private:
                Y_Disable_Copy_And_Assign(Law);
            };
        }
    }

}

#endif

