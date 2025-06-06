
#include "y/object/factory.hpp"
#include "y/memory/object/metrics.hpp"

#include "y/memory/object/blocks.hpp"
#include "y/memory/allocator/quanta.hpp"
#include "y/memory/allocator/pooled.hpp"


#include "y/xml/attribute.hpp"

#if !defined(NDEBUG)
#include "y/memory/joint/segment.hpp"
#include "y/memory/allocator/quanta.hpp"
#endif

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
    condensation( static_cast<size_t *>(Y_Memory_BZero(Condensation))-1 ),
    blocks( Memory::Object::Blocks::Instance() ),
    pooled( Memory::Pooled::Instance() ),
    quanta( Memory::Quanta::Instance() )
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
    
}

