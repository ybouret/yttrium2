
#include "y/object/factory.hpp"
#include "y/memory/small/metrics.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/quanta.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/system.hpp"
#include "y/memory/align.hpp"

#include "y/xml/attribute.hpp"

#if !defined(NDEBUG)
#include "y/memory/joint/segment.hpp"
#include "y/memory/allocator/quanta.hpp"
#endif

#include "y/exception.hpp"

namespace Yttrium
{

    Object:: Factory:: ~Factory() noexcept
    {
    }

    const char * const              Object:: Factory:: CallSign = "Object::Factory";
    const System::AtExit::Longevity Object:: Factory::LifeTime;

    static size_t Condensation[Memory::Object::Metrics::LimitObjectBytes];

    Object:: Factory:: Factory() :
    Singleton<Factory, ClassLockPolicy>(),
    Memory::Allocator(CallSign),
    condensation( static_cast<size_t *>(Y_Memory_BZero(Condensation))-1 ),
    blocks( Memory::Object::Blocks::Instance() ),
    pooled( Memory::Pooled::Instance() ),
    quanta( Memory::Quanta::Instance() ),
    sysmem( Memory::System::Instance() )
    {
        for(size_t i=1;i<=Memory::Object::Metrics::LimitObjectBytes;++i)
            Coerce(condensation[i]) = Alignment::OnLog2<CondensationShift>::Ceil(i);
    }


    void Object:: Factory:: display(std::ostream &os, size_t indent) const
    {
        initProlog(os, indent);
        os << Y_XML_Attr(LifeTime);
        initEpilog(os);
        ++indent;
        blocks.display(os,indent);
        pooled.display(os,indent);
        quanta.display(os,indent);
        --indent;
        quit(os,indent);
    }

    void * Object:: Factory:: acquireSingle(const size_t blockSize)
    {
        assert(blockSize>0);
        return blocks.acquire(blockSize);
    }

    void Object:: Factory:: releaseSingle(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(blockSize>0);
        assert(0!=blockAddr);
        blocks.release(blockAddr,blockSize);
    }

    void * Object::Factory:: acquirePooled(const size_t blockSize)
    {
        assert(blockSize>0);
        size_t       size = blockSize;
        void * const addr = pooled.acquire(size);
        assert(size>=blockSize);
        assert( Memory::Joint::Segment::Aligning::Ceil(size) == size);
        return addr;
    }

    void Object:: Factory:: releasePooled(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(blockSize>0);
        assert(0!=blockAddr);
        assert(blockSize<=Memory::Joint::Segment::Aligning::Maximum);
        void * p = blockAddr;
        size_t n = blockSize;
        pooled.release(p,n);
    }

    void * Object:: Factory:: acquireQuanta(const unsigned shift)
    {
        assert(shift<=Memory::Quanta::MaxLedgerShift);
        return quanta.acquireDyadic(shift);
    }

    void  Object:: Factory:: releaseQuanta(const unsigned shift, void * const entry) noexcept
    {
        assert(shift<=Memory::Quanta::MaxLedgerShift);
        assert(0!=entry);
        return quanta.releaseDyadic(shift,entry);
    }

#define LIMIT_OBJECT_BYTES Memory::Object::Metrics::LimitObjectBytes
#define MEDIUM_LIMIT_BYTES Memory::Object::Metrics::MediumLimitBytes




    void * Object:: Factory:: query(const size_t blockSize)
    {
        // zero size
        if(blockSize<=0)
            return 0;

        // small
        assert(blockSize>0);
        if(blockSize<=LIMIT_OBJECT_BYTES)
        {
            return acquireSingle( condensation[blockSize] );
        }

        // medium
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=MEDIUM_LIMIT_BYTES)
        {
            if( IsPowerOfTwo(blockSize) )
                return acquireQuanta( ExactLog2(blockSize) );
            return acquirePooled(blockSize);
        }

        // quanta
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=Memory::Quanta::MaxLedgerBytes)
        {
            return acquireQuanta( CeilLog2(blockSize) );
        }


        // bigger: aligned blockSize
        return sysmem.acquire( Coerce(blockSize) );
    }

    void * Object:: Factory:: acquireBlock(size_t &blockSize)
    {
        assert(blockSize>0);

        // small
        if(blockSize<=LIMIT_OBJECT_BYTES)
        {
            return acquireSingle( blockSize = condensation[blockSize] );
        }

        // medium
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=MEDIUM_LIMIT_BYTES)
        {
            if( IsPowerOfTwo(blockSize) )
                return acquireQuanta( ExactLog2(blockSize) );
            return pooled.acquireBlock(blockSize);
        }

        // quanta
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=Memory::Quanta::MaxLedgerBytes)
        {
            return quanta.acquire(blockSize);
        }

        // bigger ?
        return sysmem.acquire(blockSize);
    }


    void Object:: Factory:: store(void * const blockAddr, const size_t blockSize) noexcept
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
            return releaseSingle(blockAddr,condensation[blockSize]);
        }

        // medium
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=MEDIUM_LIMIT_BYTES)
        {
            if(IsPowerOfTwo(blockSize))
                return releaseQuanta( ExactLog2(blockSize), blockAddr);
            return releasePooled(blockAddr,blockSize);
        }

        // quanta
        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=Memory::Quanta::MaxLedgerBytes)
        {
            return releaseQuanta(CeilLog2(blockSize),blockAddr);
        }

        // bigger ?
        void * addr = blockAddr;
        size_t size = Memory::Align::Compute::Ceil(blockSize);
        return sysmem.release(addr,size);

    }

    void Object:: Factory:: releaseBlock(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(0!=blockAddr);
        assert(blockSize>0);

        if(blockSize<=LIMIT_OBJECT_BYTES)
        {
            assert( condensation[blockSize] == blockSize );
            return releaseSingle(blockAddr,blockSize);
        }

        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=MEDIUM_LIMIT_BYTES)
        {
            if(IsPowerOfTwo(blockSize))
                return releaseQuanta( ExactLog2(blockSize), blockAddr);
            return pooled.releaseBlock(blockAddr,blockSize);
        }

        assert(blockSize>LIMIT_OBJECT_BYTES);
        if(blockSize<=Memory::Quanta::MaxLedgerBytes)
        {
            assert(IsPowerOfTwo(blockSize));
            return quanta.releaseDyadic(ExactLog2(blockSize), blockAddr);
        }

        void * addr = blockAddr;
        size_t size = blockSize; assert( size == Memory::Align::Compute::Ceil(blockSize) );

        return sysmem.release(addr,size);

    }




}

