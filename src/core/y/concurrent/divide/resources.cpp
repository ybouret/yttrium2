
#include "y/concurrent/divide/resources.hpp"
#include "y/object/factory.hpp"
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
        void * acquireResources( const size_t blockSize )
        {
            static Object::Factory &factory = Object::Factory::Instance();
            return factory.query(blockSize);
        }

        void Resources:: release() noexcept
        {
            if(blockSize>0)
            {
                static Object::Factory &factory = Object::Factory::Location();
                assert(0!=blockAddr);
                factory.store(memset(blockAddr,0,blockSize),blockSize);
                Coerce(blockAddr) = 0;
                Coerce(blockSize) = 0;
            }
            else
            {
                assert(0==blockAddr);
            }
            
        }



        void Resources:: ensure(const size_t capacity)
        {
            if(blockSize<capacity)
            {
                void * tmp = acquireResources(capacity);
                release();
                Coerce(blockSize) = capacity;
                Coerce(blockAddr) = tmp;
            }
        }




        Resources:: ~Resources() noexcept
        {
            release();
        }

    }

}
