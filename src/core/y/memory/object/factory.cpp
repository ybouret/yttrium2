
#include "y/memory/object/factory.hpp"
#include "y/xml/attribute.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/check/static.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/joint/segment.hpp"

#include "y/exception.hpp"

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


            static size_t Condensation[Factory::LIMIT_OBJECT_BYTES];

            Factory:: Factory() :
            FactoryAPI(DEFAULT_PAGE_BYTES),
            condensation( static_cast<size_t *>(Y_Memory_BZero(Condensation))-1 ),
            pooled( Memory::Pooled::Instance() )
            {
                for(size_t i=1;i<=LIMIT_OBJECT_BYTES;++i)
                {
                    Coerce(condensation[i]) = Alignment::OnLog2<CONDENSATION_SHIFT>::Ceil(i);
                    std::cerr << i << " => " << condensation[i] << std::endl;
                }
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
                void * const addr = pooled.acquire(size);
                assert(size>=blockSize);
                assert( Joint::Segment::Aligning::Ceil(size) == size);
                return addr;
            }

            void Factory:: releaseJoint(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                assert(0!=blockAddr);
                assert(blockSize<=Joint::Segment::Aligning::Maximum);
                void * p = blockAddr;
                size_t n = blockSize;
                pooled.release(p,n);
            }



            void * Factory:: acquire(const size_t blockSize)
            {
                // zero size
                if(blockSize<=0)
                    return 0;

                // small
                assert(blockSize>0);
                if(blockSize<=LIMIT_OBJECT_BYTES)
                    return acquireBlock( condensation[blockSize] );

                // medium
                assert(blockSize>LIMIT_OBJECT_BYTES);


                throw Exception("Not Implemented");
            }


            void Factory:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                if(blockSize<=0)
                {
                    assert(0==blockAddr);
                    return;
                }

                assert(blockSize>0);
                if(blockSize<=LIMIT_OBJECT_BYTES)
                    return releaseBlock( blockAddr, condensation[blockSize] );

                assert(blockSize>LIMIT_OBJECT_BYTES);
            }


        }

    }

}
