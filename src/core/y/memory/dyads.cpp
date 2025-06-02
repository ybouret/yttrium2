
#include "y/memory/dyads.hpp"
#include "y/memory/object/factory.hpp"
#include "y/memory/object/guild.hpp"
#include "y/memory/workspace.hpp"

namespace Yttrium
{
    namespace Memory
    {

        const char * const Dyads:: CallSign = "Memory::Dyads";

        Dyads:: Manager:: Manager(const unsigned int blockShift) noexcept :
        shift( blockShift ),
        bytes( size_t(1) << blockShift )
        {

        }

        Dyads:: Manager:: ~Manager() noexcept
        {

        }

        namespace
        {
            class ObjectManager :
            public Dyads::Manager,
            public Object::Guild
            {
            public:
                inline explicit ObjectManager(const unsigned blockShift) :
                Dyads::Manager(blockShift),
                Object::Guild(bytes)
                {
                }

                inline virtual ~ObjectManager() noexcept
                {
                }


            private:
                Y_Disable_Copy_And_Assign(ObjectManager);
            };

            class ObjectManagers : public Workspace<ObjectManager,Dyads::NumFactoryShift>
            {
            public:
                inline explicit ObjectManagers() :
                Workspace<ObjectManager,Dyads::NumFactoryShift>()
                {
                }

                inline virtual ~ObjectManagers() noexcept
                {

                }

            private:
                Y_Disable_Copy_And_Assign(ObjectManagers);
                inline void release(size_t built) noexcept
                {
                    
                }

            };

        }



        class Dyads:: Code
        {
        public:
            explicit Code()
            {
            }

            inline ~Code() noexcept
            {
            }
            
        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace {
            static void * codeWorkspace[ Alignment::WordsFor<Dyads::Code>::Count ];
        }


        Dyads:: Dyads() :
        Singleton<Dyads, DyadsLockPolicy>(),
        code( new (Y_Memory_BZero(codeWorkspace)) Code()  )
        {

        }

        Dyads:: ~Dyads() noexcept
        {
            assert(0!=code);
            (void) Stealth::DestructedAndZeroed(code);
            Coerce(code) = 0;
        }

    }

}
