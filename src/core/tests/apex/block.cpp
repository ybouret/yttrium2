#include "y/apex/m/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/utils.hpp"
#include "y/object.hpp"
#include "y/apex/block/blocks.hpp"
#include "y/apex/block/transmogrify.hpp"
#include "y/apex/block/model.hpp"


namespace Yttrium
{
    namespace Apex
    {
        

     




    }
}

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    struct Blk
    {
        unsigned shift;
        void *   entry;
    };

    static const size_t MaxBlk = 30;
    static Blk          Blks[MaxBlk];
}

Y_UTEST(apex_block)
{
    System::Rand ran;

    Y_PRINTV(Apex::Archon::NumShifts);

    Apex::Archon & mgr = Apex::Archon::Instance();


    if(true)
    {
        mgr.display(std::cerr,0);
        Y_Memory_BZero(Blks);
        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            while( (b.shift = unsigned(ran.in(20)) ) < Apex::Archon::MinShift )
                ;
            b.entry = mgr.query(b.shift);
        }
        ran.shuffle(Blks,MaxBlk);

        mgr.display(std::cerr,0);

        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            mgr.store(b.shift,b.entry);
        }
        mgr.display(std::cerr,0);
    }



    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint16_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint32_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint64_t>) );

    Y_PRINTV( Apex::Blocks::BlockProtoSize );
    Y_SIZEOF( Apex::Blocks );

    const uint64_t p64[2] = { 0xabdc, 0x1234 };
    {
        Apex::Blocks b(0);

        Apex::Block<uint64_t> &b64 = b.block<uint64_t>();
        b64.data[0] = p64[0];
        b64.data[1] = p64[1];
        b64.size    = 2;
        Y_ASSERT(b64.isValid());
        const size_t numBits = b64.update(b.sync[3]);
        std::cerr << "numBits=" << numBits << std::endl;

        Apex::Block<uint32_t> &b32 = b.block<uint32_t>();
        Apex::Block<uint16_t> &b16 = b.block<uint16_t>();
        Apex::Block<uint8_t>  &b8  = b.block<uint8_t>();

        std::cerr << "#64 = " << b64.size << std::endl;
        std::cerr << "#32 = " << b32.size << std::endl;
        std::cerr << "#16 = " << b16.size << std::endl;
        std::cerr << "#8  = " << b8.size << std::endl;


        std::cerr << "I/O with 64 bits" << std::endl;
        std::cerr << b64 << std::endl;
        Apex::Transmogrify::To(b32,b64);
        std::cerr << b32 << std::endl;
        Apex::Transmogrify::To(b64,b32);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        Apex::Transmogrify::To(b16,b64);
        std::cerr << b16 << std::endl;
        Apex::Transmogrify::To(b64,b16);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        Apex::Transmogrify::To(b8,b64);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b64,b8);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        std::cerr << "I/O with 32 bits" << std::endl;
        Apex::Transmogrify::To(b32,b64);
        uint32_t p32[4] = { 0 };
        memcpy(p32,b32.data,sizeof(p32));
        Apex::Transmogrify::To(b16,b32);
        std::cerr << b16 << std::endl;
        Apex::Transmogrify::To(b32,b16);
        std::cerr << b32 << std::endl; Y_ASSERT( 0 == memcmp(b32.data,p32,sizeof(p32)));

        Apex::Transmogrify::To(b8,b32);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b32,b8);
        std::cerr << b32 << std::endl; Y_ASSERT( 0 == memcmp(b32.data,p32,sizeof(p32)));


        std::cerr << "I/O with 16 bits" << std::endl;
        Apex::Transmogrify::To(b16,b32);
        uint16_t p16[8] = { 0 };
        memcpy(p16,b16.data,sizeof(p16));
        Apex::Transmogrify::To(b8,b16);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b16,b8);
        std::cerr << b16 << std::endl; Y_ASSERT( 0 == memcmp(b16.data,p16,sizeof(p16)));
    }


    {
        std::cerr << "Using Models" << std::endl;
        Apex::Model m(10,Apex::View64);


        m.get<uint64_t>().data[0] = p64[0];
        m.get<uint64_t>().data[1] = p64[1];
        m.get<uint64_t>().size    = 2;
        m.update();

        Y_ASSERT(m.get<uint64_t>().isValid());

        std::cerr << "Printing..." << std::endl;
        std::cerr << m.make<uint64_t>() << std::endl;
        std::cerr << m.make<uint32_t>() << std::endl;
        std::cerr << m.make<uint16_t>() << std::endl;
        std::cerr << m.make<uint8_t>() << std::endl;

    }

}
Y_UDONE()

