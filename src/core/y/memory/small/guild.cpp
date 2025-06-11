
#include "y/memory/small/guild.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
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
                    static Blocks & B = Blocks::Instance();
                    void * const    p = B.acquire( sizeof(Code) );
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
                std::cerr << "~Guild[" << getBlockSize() << "]/sizeof(Code)=" << sizeof(Code) << std::endl;
                assert( 0 != code);
                assert( Blocks::Exists() );
                static Blocks & B = Blocks::Location();
                B.release( Stealth::DestructedAndZeroed(code), sizeof(Code) );
                B.sort();
                B.display(std::cerr,0);
            }

            size_t Guild:: getBlockSize() const noexcept
            {
                assert( 0 != code);
                return code->arena.blockSize;
            }

            void * Guild:: acquireBlockUnlocked()
            {
                assert(0!=code);
                return code->arena.acquire();
            }

            void Guild:: releaseBlockUnlocked(void * const addr) noexcept
            {
                assert(0!=addr); assert(owns(addr));
                assert(0!=code);
                code->arena.release(addr);
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
                assert(0!=addr);
                assert( owns(addr) );
                Y_Lock(code->access);
                code->arena.release(addr);
            }

            bool Guild:: owns(const void * const addr) const noexcept
            {
                assert(0!=code);
                Y_Lock(code->access);
                return code->arena.owns(addr);
            }


            Y_Ingress_Impl(Guild,code->access)


        }
    }

}
