
#include "y/apex/block/blocks.hpp"
#include "y/apex/m/archon.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Blocks:: Blocks(const size_t userBytes) :
        base(0),
        sync(),
        wksp(),
        dataShift(0),
        dataBytes( Metrics::BytesFor(userBytes,dataShift) ),
        dataEntry( Query(dataShift) )
        {
            setup();
        }


        Blocks:: Blocks(const Blocks &other) :
        base(0),
        sync(),
        wksp(),
        dataShift(0),
        dataBytes( Metrics::BytesFor(other.block<uint8_t>().size,dataShift) ),
        dataEntry( Query(dataShift) )
        {
            setup();
            const size_t toCopy =
            block<uint8_t>() .size = other.block<uint8_t>() .size;
            block<uint16_t>().size = other.block<uint16_t>().size;
            block<uint32_t>().size = other.block<uint32_t>().size;
            block<uint64_t>().size = other.block<uint64_t>().size;
            memcpy(dataEntry,other.dataEntry,toCopy);
        }

        Blocks:: ~Blocks() noexcept
        {
            static Archon &archon = Archon::Location();
            archon.store(dataShift,dataEntry);
        }

        void * Blocks:: Query(const unsigned shift)
        {
            static Archon &archon = Archon::Instance();
            return archon.query(shift);
        }

        void Blocks:: setup() noexcept
        {
            // base address
            Coerce(base) = static_cast<uint8_t *>( Y_Memory_BZero(wksp) );

            {
                // dress up blocks
                new (base)                  Block<uint8_t>(  dataEntry, dataBytes     );
                new (base+  BlockProtoSize) Block<uint16_t>( dataEntry, dataBytes >> 1);
                new (base+2*BlockProtoSize) Block<uint32_t>( dataEntry, dataBytes >> 2);
                new (base+3*BlockProtoSize) Block<uint64_t>( dataEntry, dataBytes >> 3);
            }

            {
                // record sync
                Block<uint8_t>  & b8  = block<uint8_t>();
                Block<uint16_t> & b16 = block<uint16_t>();
                Block<uint32_t> & b32 = block<uint32_t>();
                Block<uint64_t> & b64 = block<uint64_t>();

                Coerce(sync[0][0]) = &b16; Coerce(sync[0][1]) = &b32; Coerce(sync[0][2]) = &b64;
                Coerce(sync[1][0]) = &b8;  Coerce(sync[1][1]) = &b32; Coerce(sync[1][2]) = &b64;
                Coerce(sync[2][0]) = &b8;  Coerce(sync[2][1]) = &b16; Coerce(sync[2][2]) = &b64;
                Coerce(sync[3][0]) = &b8;  Coerce(sync[3][1]) = &b16; Coerce(sync[3][2]) = &b32;
            }
        }

    }
}


