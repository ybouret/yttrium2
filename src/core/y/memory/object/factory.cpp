
#include "y/memory/object/factory.hpp"
#include "y/xml/attribute.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/memory/object/ledger.hpp"
#include "y/check/static.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/quanta.hpp"
#include "y/memory/joint/segment.hpp"

#include "y/exception.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

#if 0
            const size_t   Factory:: MEDIUM_LIMIT_BYTES = Joint::Segment::MaxSizeFor( DEFAULT_PAGE_SHIFT );

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
                }
            }

            void Factory:: display(std::ostream &os, size_t indent) const
            {
                initProlog(os, indent);
                os << Attribute("LifeTime",LifeTime);
                initEpilog(os);
                ++indent;
                blocks.display(os,indent);
                pooled.display(os,indent);
                Quanta::Instance().display(os,indent);
                --indent;
                quit(os,indent);
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


            void * Factory:: acquireQuanta(const unsigned shift)
            {
                assert(shift<=Quanta::MaxAllowedShift);
                static Quanta * Q  = 0;
                Y_Lock(access);
                if(!Q)
                    Q = & Quanta::Instance();
                return Q->acquireDyadic(shift);
            }

            void Factory:: releaseQuanta(const unsigned shift, void * const entry) noexcept
            {
                assert(shift<=Quanta::MaxAllowedShift);
                assert(0!=entry);
                assert( Quanta::Exists() );
                static Quanta &Q = Quanta::Location();
                Q.releaseDyadic(shift,entry);
            }


            void * Factory:: acquire(const size_t blockSize)
            {
                // zero size
                if(blockSize<=0)
                    return 0;

                // small
                assert(blockSize>0);
                if(blockSize<=LIMIT_OBJECT_BYTES)
                {

                    return acquireBlock( condensation[blockSize] );
                }

                // medium
                assert(blockSize>LIMIT_OBJECT_BYTES);
                if(blockSize<=MEDIUM_LIMIT_BYTES)
                {
                    if( IsPowerOfTwo(blockSize) )
                        return acquireQuanta( ExactLog2(blockSize) );
                    return acquireJoint(blockSize);
                }




                throw Exception("Not Implemented");
            }


            void Factory:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                // zero size
                if(blockSize<=0)
                {
                    assert(0==blockAddr);
                    return;
                }

                // small
                assert(blockSize>0);
                if(blockSize<=LIMIT_OBJECT_BYTES)
                {
                    return releaseBlock(blockAddr,condensation[blockSize]);
                }

                // medium
                assert(blockSize>LIMIT_OBJECT_BYTES);
                if(blockSize<=MEDIUM_LIMIT_BYTES)
                {
                    if(IsPowerOfTwo(blockSize))
                        return releaseQuanta( ExactLog2(blockSize), blockAddr);
                    return releaseJoint(blockAddr,blockSize);
                }
                

            }

#endif
            
        }

    }

}
