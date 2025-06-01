
//! \file

#ifndef Y_Memory_Object_Guild_Included
#define Y_Memory_Object_Guild_Included 1

#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Guild
            {
            public:
                class Code;

                explicit Guild(const size_t blockSize);
                virtual ~Guild() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Guild);
                Code * const code;
            };
        }
    }

}

#endif

