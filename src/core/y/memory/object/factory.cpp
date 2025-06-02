
#include "y/memory/object/factory.hpp"
#include "y/xml/attribute.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/check/static.hpp"
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
            FactoryAPI(DEFAULT_PAGE_BYTES)
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

        }

    }

}
