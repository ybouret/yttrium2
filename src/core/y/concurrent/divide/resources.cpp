
#include "y/concurrent/divide/resources.hpp"
#include "y/object/factory.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {

        Resources:: Resources() noexcept :
        blockSize(0),
        blockAddr(0)
        {

        }



        static inline
        void * acquireResources( size_t &blockSize )
        {
            static Memory::Allocator &mgr = Memory::Dyadic::Instance();
            return mgr.acquire(blockSize);
        }

        void Resources:: release() noexcept
        {
            if(blockSize>0)
            {
                static Memory::Allocator &mgr = Memory::Dyadic::Location();
                assert(0!=blockAddr);
                mgr.release(Coerce(blockAddr),Coerce(blockSize));
                assert(0==blockAddr);
                assert(0==blockSize);
            }
            else
            {
                assert(0==blockAddr);
            }
            
        }



        void Resources:: ensure(size_t capacity)
        {
            if(blockSize<capacity)
            {
                void * tmp = acquireResources(capacity);
                release();
                Coerce(blockSize) = capacity;
                Coerce(blockAddr) = tmp;
            }
            else
            {
                memset(blockAddr,0,blockSize);
            }
        }




        Resources:: ~Resources() noexcept
        {
            release();
        }

    }

}
