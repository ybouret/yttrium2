
#include "y/field/sketch.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

    namespace Field
    {

        Sketch:: ~Sketch() noexcept
        {
            if(wlen)
            {
                assert(wksp);
                Free(wksp,wlen);
            }
        }

        const String & Sketch:: key() const noexcept { return name; }

        void * Sketch:: Make(size_t &bytes)
        {
            assert(bytes>0);
            static Memory::Allocator & mgr = Object::AllocatorInstance();
            return mgr.acquire(bytes);
        }

        void Sketch:: Free(void * & wksp, size_t & wlen) noexcept
        {
            assert(wksp);
            assert(wlen>0);
            static Memory::Allocator & mgr = Object::AllocatorLocation();
            mgr.release(wksp,wlen);
        }

    }

}

