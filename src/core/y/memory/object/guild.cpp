
#include "y/memory/object/guild.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Guild:: Code
            {
            public:

                inline Code(Lockable &theAccess,
                            Arena    &theArena) :
                access(theAccess),
                arena(theArena)
                {

                }


                inline ~Code() noexcept
                {
                }

                static inline
                Code * Create(const size_t blockSize)
                {
                    Blocks  &    B = Blocks::Instance();
                    void * const p = B.acquire( sizeof(Code) );
                    try
                    {
                        return new (p) Code(B.access,B.getArenaFor(blockSize));
                    }
                    catch(...)
                    {
                        B.release(p,sizeof(Code));
                        throw;
                    }
                }

                Lockable & access;
                Arena    & arena;

            private:
                Y_Disable_Copy_And_Assign(Code);
            };



            Guild:: Guild(const size_t userBlockSize) :
            code( Code::Create(userBlockSize) )
            {
            }


            Guild:: ~Guild() noexcept
            {
                assert( 0!= code);
                assert( Blocks::Exists() );
                Blocks::Location().release( Stealth::DestructedAndZeroed(code), sizeof(Code) );
            }

            size_t Guild:: blockSize() const noexcept
            {
                assert( 0 != code);
                return code->arena.blockSize;
            }

            void * Guild:: acquireBlock()
            {
                assert(0!=code);
                Y_Lock(code->access);
                return code->arena.acquire();
            }

            void Guild:: releaseBlock(void * const addr) noexcept
            {
                assert(0!=code);
                Y_Lock(code->access);
                code->arena.release(addr);
            }



        }
    }

}
