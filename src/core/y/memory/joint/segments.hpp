
//! \file

#ifndef Y_Memory_Joint_Segments_Included
#define Y_Memory_Joint_Segments_Included 1

#include "y/core/setup.hpp"
#include "y/core/linked/list.hpp"
#include "y/memory/joint/segment.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Dyadic;

        namespace Joint
        {

            class Segments
            {
            public:
                explicit Segments();
                virtual ~Segments() noexcept;

                void release(void * const blockAddr) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Segments);

                void unload(Segment * const segment) noexcept;

                Segment *              acquiring;
                Core::ListOf<Segment>  list;
                Dyadic               & dyadic;
            };

        }

    }

}

#endif

