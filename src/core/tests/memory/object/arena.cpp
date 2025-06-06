
#include "y/memory/object/arena.hpp"
#include "y/memory/stealth.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/check/usual.hpp"
#include "y/memory/object/ledger.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{
	static const size_t MaxSize = 1000;

	static inline
		void fill(void* addr[], size_t& size, Memory::Object::Arena& arena)
	{
		while (size < MaxSize)
			addr[size++] = arena.acquire();
	}

	static inline
		void empty(const size_t to, void* addr[], size_t& size, Memory::Object::Arena& arena, System::Rand& ran)
	{
		ran.shuffle(addr, size);
		while (size > to)
		{
			arena.release(addr[--size]);
		}
	}

}

Y_UTEST(memory_object_arena)
{
	System::Rand ran;
	Y_SIZEOF(Memory::Object::Arena);

    size_t maxBlockSize = 16;
    if(argc>1) maxBlockSize = size_t( atol(argv[1]) );

    void* addr[MaxSize];
    size_t size = 0;
    Y_Memory_BZero(addr);

    for(size_t blockSize=1;blockSize<=maxBlockSize;++blockSize)
    {
        std::cerr << "[blockSize=" << std::setw(3) << blockSize << "][";
        for(size_t pageBytes = 128; pageBytes <= 8192; pageBytes <<= 1)
        {
            (std::cerr << '.').flush();

            Memory::Object::Arena arena(blockSize, pageBytes);

            fill(addr, size, arena);
            for (int iter = 0; iter < 100; ++iter)
            {
                empty(size >> 1, addr, size, arena, ran);
                fill(addr, size, arena);
            }
            empty(0, addr, size, arena, ran);
        }
        std::cerr << "]" << std::endl;
    }

    Memory::Object::Book::Location().display(std::cerr,0);

    Y_SIZEOF(Memory::Object::Arena);

}
Y_UDONE()
