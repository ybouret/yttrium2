
#include "y/memory/management/dead-pool.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"

using namespace Yttrium;


namespace
{
    static const size_t Maxi = 1000;
    static void *       addr[Maxi];
    static size_t       size = 0;

    static inline void fill(Memory::DeadPool &z)
    {
        while(size<Maxi)
        {
            addr[size] = z.query();
            ++size;
        }
    }


    static inline void empty(const size_t to, Memory::DeadPool &z, System::Rand &ran)
    {
        ran.shuffle(addr,size);
        while(size>to)
            z.store( addr[--size] );
        z.gc( ran.gen<uint8_t>( unsigned(ran.leq(6)) ) );
    }

}

Y_UTEST(memory_dead_pool)
{

    System::Rand     ran;
    Memory::DeadPool pool(12);

    Y_Memory_BZero(addr);

    fill(pool);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(size>>1,pool,ran);
        fill(pool);
    }
    empty(0,pool,ran);





}
Y_UDONE()
