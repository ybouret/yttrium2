
#include "y/memory/dyads.hpp"
#include "y/memory/object/factory.hpp"
#include "y/memory/object/guild.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/workspace/cxx.hpp"
#include "y/xml/attribute.hpp"

#include <iostream>

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
                    std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~ObjectManager() noexcept
                {
                }

                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) ObjectManager(unsigned(blockShift));
                }

            private:
                Y_Disable_Copy_And_Assign(ObjectManager);
            };

            

        }

        namespace
        {
            class DyadicManager : public Dyads::Manager
            {
            public:
                inline explicit DyadicManager(const unsigned blockShift) :
                Dyads::Manager(blockShift),
                dyadic( Dyadic::Instance() )
                {
                    std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~DyadicManager() noexcept {}

                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) DyadicManager(unsigned(blockShift));
                }

                Memory::Dyadic &dyadic;

            private:
                Y_Disable_Copy_And_Assign(DyadicManager);
            };


        }



        class Dyads:: Code
        {
        public:
            explicit Code() :
            manager(),
            objectManager(Procedural,ObjectManager::Create,0),
            dyadicManager(Procedural,DyadicManager::Create,NumFactoryShift)
            {
                Y_Memory_BZero(manager);

                for(unsigned i=0;i<=MaxFactoryShift;++i)
                {
                    manager[i] = &objectManager[i+1];
                    assert(i==manager[i]->shift);
                }

                for(unsigned i=0;i<NumGreaterShift;++i)
                {
                    manager[i+NumFactoryShift] = &dyadicManager[i+1];
                    assert(i+NumFactoryShift==manager[i+NumFactoryShift]->shift);
                }

            }

            inline ~Code() noexcept
            {
            }

            Manager *                                   manager[MaxAllowedShift+1];
            CxxWorkspace<ObjectManager,NumFactoryShift> objectManager;
            CxxWorkspace<DyadicManager,NumGreaterShift> dyadicManager;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace {
            static void * codeWorkspace[ Alignment::WordsFor<Dyads::Code>::Count ];
        }


        const unsigned Dyads:: NumFactoryShift;
        const unsigned Dyads:: NumGreaterShift;

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

        void Dyads:: display(std::ostream &os, size_t indent) const
        {
            initProlog(os,indent)
            << Attribute("NumFactoryShift",NumFactoryShift)
            << Attribute("NumGreaterShift",NumGreaterShift);
            initEpilog(os,false);

            ++indent;
            Memory::Dyadic::Location().display(os,indent);
            --indent;

            quit(os,indent);
        }

    }

}
