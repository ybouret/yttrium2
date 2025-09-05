#include "y/string/stride/metrics.hpp"
#include "y/core/utils.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    namespace Core
    {



        StrideMetrics:: StrideMetrics(const size_t minimalCapacity,
                                      const size_t blockSize) noexcept :
        size(0),
        capacity( Max<size_t>(minimalCapacity,7) ),
        address(0),
        numChars( capacity+1 ),
        obtained( numChars * blockSize )
        {
            assert(blockSize>0);
            static Memory::Pooled &mgr = Memory::Pooled::Instance();
            Coerce(address)  = mgr.acquire( Coerce(obtained) ); assert( obtained >= numChars * blockSize );
            Coerce(numChars) = obtained / blockSize;
            Coerce(capacity) = numChars - 1;
            assert( isValidWith(blockSize) );
        }

        StrideMetrics:: ~StrideMetrics() noexcept
        {
            assert(numChars-1==capacity);
            assert(capacity>0);
            assert(size<=capacity);
            assert(obtained>=numChars);
            assert( Memory::Pooled::Exists() );

            static Memory::Pooled & mgr = Memory::Pooled::Location();
            mgr.release( Coerce(address), Coerce(obtained) );
            Coerce(numChars) = 0;
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }

        const char * StrideMetrics:: asChar(const IntToType<false> &) const noexcept
        {
            static const char empty[4] = { 0,0,0,0 };
            return empty;
        }

        const char * StrideMetrics:: asChar(const IntToType<true> &) const noexcept
        {
            return static_cast<const char *>(address);
        }



    }

}

#include <iostream>
#include "y/memory/stealth.hpp"
//#include "y/memory/joint/segment.hpp"

namespace Yttrium
{

    namespace Core
    {
#define SANITY(EXPR) do { if( !(EXPR) ) { std::cerr << "*** " << #EXPR << " failure" << std::endl; return false; } } while(false)


#if 0
        namespace
        {
            typedef Memory::Joint::Segment Segment;
            typedef Segment::Block         Block;
        }
#endif
        
        bool StrideMetrics:: isValidWith(const size_t blockSize) const noexcept
        {
            SANITY(size<=capacity);
            SANITY(numChars-1==capacity);
            SANITY(0!=address);
            const uint8_t * const org       = (const uint8_t *)address;
            const uint8_t * const freeSpace = org + (blockSize*size);
            const size_t          freeBytes = (numChars-size)*blockSize;
            SANITY(Memory::Stealth::Are0(freeSpace,freeBytes));
            //const Block * const block = Segment::GetBlockOf(address);
            //SANITY(0!=block);

            return true;
        }


        

    }

}


