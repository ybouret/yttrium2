
#include "y/memory/allocator/quanta.hpp"
#include "y/memory/object/factory.hpp"
#include "y/memory/object/guild.hpp"
#include "y/memory/object/book.hpp"
#include "y/memory/allocator/dyadic.hpp"

#include "y/memory/workspace/cxx.hpp"
#include "y/xml/attribute.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        const char * const Quanta:: CallSign = "Memory::Quanta";

        Quanta:: Manager:: Manager(const unsigned int blockShift) noexcept :
        shift( blockShift ),
        bytes( size_t(1) << blockShift )
        {

        }

        Quanta:: Manager:: ~Manager() noexcept
        {

        }

        namespace
        {
            class ObjectManager :
            public Quanta::Manager,
            public Object::Guild
            {
            public:
                inline explicit ObjectManager(const unsigned blockShift) :
                Quanta::Manager(blockShift),
                Object::Guild(bytes)
                {
                    std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~ObjectManager() noexcept
                {
                }

                inline virtual void * acquire()
                {
                    return acquireBlock();
                }

                inline virtual void   release(void * const addr) noexcept
                {
                    assert(0!=addr);
                    releaseBlock(addr);
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
            class DyadicManager : public Quanta::Manager
            {
            public:
                inline explicit DyadicManager(const unsigned blockShift) :
                Quanta::Manager(blockShift),
                dyadic( Dyadic::Instance() )
                {
                    std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~DyadicManager() noexcept {}

                inline virtual void *acquire()
                {
                    return dyadic.acquireDyadic(shift);
                }

                inline virtual void   release(void * const addr) noexcept
                {
                    assert(0!=addr);
                    return dyadic.releaseDyadic(addr,shift);
                }

                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) DyadicManager(unsigned(blockShift));
                }

                Memory::Dyadic &dyadic;

            private:
                Y_Disable_Copy_And_Assign(DyadicManager);
            };


        }



        class Quanta:: Code
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
            static void * codeWorkspace[ Alignment::WordsFor<Quanta::Code>::Count ];
        }


        const unsigned Quanta:: NumFactoryShift;
        const unsigned Quanta:: NumGreaterShift;

        Quanta:: Quanta() :
        Singleton<Quanta, QuantaLockPolicy>(),
        code( new (Y_Memory_BZero(codeWorkspace)) Code()  )
        {
        }

        Quanta:: ~Quanta() noexcept
        {
            assert(0!=code);
            (void) Stealth::DestructedAndZeroed(code);
            Coerce(code) = 0;
        }

        void Quanta:: display(std::ostream &os, size_t indent) const
        {
            assert(0!=code);
            initProlog(os,indent)
            << Attribute("NumFactoryShift",NumFactoryShift)
            << Attribute("NumGreaterShift",NumGreaterShift);
            initEpilog(os,false);

            ++indent;
            Memory::Dyadic::Location().display(os,indent);
            --indent;

            quit(os,indent);
        }

        void * Quanta:: acquireDyadic(const unsigned int blockShift)
        {
            assert(blockShift<=MaxAllowedShift);
            assert(blockShift==code->manager[blockShift]->shift);
            return code->manager[blockShift]->acquire();
        }

    }

}
