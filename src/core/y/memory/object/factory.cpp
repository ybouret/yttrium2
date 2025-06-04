
#include "y/memory/object/factory.hpp"
#include "y/xml/attribute.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/check/static.hpp"
#include "y/memory/allocator/pooled.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            Factory:: ~Factory() noexcept
            {
            }

            Factory:: Factory() :
            FactoryAPI(DEFAULT_PAGE_BYTES),
            pooled( Memory::Pooled::Instance() )
            {
            }

            void Factory:: display(std::ostream &os, size_t indent) const
            {
                initProlog(os, indent);
                os << Attribute("LifeTime",LifeTime);
                initEpilog(os);
            }

            void * Factory:: acquireBlock(const size_t blockSize)
            {
                assert(blockSize>0);
                Y_Lock(access);
                return blocks.acquire(blockSize);
            }

            void Factory:: releaseBlock(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                assert(0!=blockAddr);
                Y_Lock(access);
                blocks.release(blockAddr,blockSize);
            }

            void * Factory:: acquireJoint(const size_t blockSize)
            {
                assert(blockSize>0);
                size_t       size = blockSize;
                void * const addr = pooled.acquire(size); assert(size>=blockSize);
                return addr;
            }

            void Factory:: releaseJoint(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                assert(0!=blockAddr);
                void * p = blockAddr;
                size_t n = blockSize;
                pooled.release(p,n);
            }



        }

    }

}
