
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
                
                explicit Guild(const size_t userBlockSize);
                virtual ~Guild() noexcept;

                size_t blockSize() const noexcept;
                void * acquireBlock();
                void   releaseBlock(void * const) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Guild);
                Code * const code;
            };

            template <typename T>
            class GuildOf : public Guild
            {
            public:
                inline explicit GuildOf() : Guild(sizeof(T)) {}
                inline virtual ~GuildOf() noexcept {}

                

            private:
                Y_Disable_Copy_And_Assign(GuildOf);
            };

        }
    }

}

#endif

