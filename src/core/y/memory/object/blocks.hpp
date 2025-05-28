
//! \file

#ifndef Y_Memory_Blocks_Included
#define Y_Memory_Blocks_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {
            class Blocks : public Singleton<Blocks,GiantLockPolicy>
            {
            public:
                static const char * const CallSign;                                     //!< "Memory::Object::Blocks"
                static const Longevity    LifeTime     = LifeTimeOf:: MemoryObjectBook; //!< LifeTimeOf::MemoryObjectBlocks

            private:
                Y_Disable_Copy_And_Assign(Blocks);

                explicit Blocks() noexcept;
                virtual ~Blocks() noexcept;
            };
        }
    }

}

#endif

