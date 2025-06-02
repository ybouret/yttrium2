

#include "y/memory/joint/segments.hpp"
#include "y/memory/allocator/dyadic.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Joint
        {

            Segments:: Segments() :
            acquiring(0),
            list(),
            dyadic( Dyadic::Instance() )
            {
            }


            Segments:: ~Segments() noexcept
            {
                while(list.size) unload( list.popTail() );
            }

            void Segments:: unload(Segment * const segment) noexcept
            {

                assert(0!=segment);
                assert(0==segment->next);
                assert(0==segment->prev);
                assert(Dyadic::Exists());

                // check errors ?
                Segment::Param &param = segment->param;
                assert(param.isDyadic);
                dyadic.releaseDyadic(segment,param.shift);
            }


            void Segments:: release(void * const blockAddr) noexcept
            {
                assert(0!=blockAddr);
                Segment * const segment = Segment::Release(blockAddr);
                assert(0!=segment);
                assert(list.owns(segment));

            }


        }

    }

}


